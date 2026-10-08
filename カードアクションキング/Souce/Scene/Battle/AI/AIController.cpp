#include "AIController.h"

//ライブラリ
#include <vector>
#include <random>
#include <utility>

//battleマネージャー
#include "../BattleManager.h"

//プレイヤー
#include "../Player/BattlePlayer.h"

//battle関連
#include "../BattleConfig.h"
#include "../board/Board.h"
#include "../board/Cell/Cell.h"

#include "../../../card/data/Pattern/PatternDatabase.h"

//初期化
bool AIController::Init(
    BattleManager* battleManager,
    UnitOwner owner)
{
    if (battleManager == nullptr)
    {
        return false;
    }

    m_battleManager = battleManager;
    m_owner = owner;

    Reset();

    return true;
}

// AI開始
void AIController::Start()
{
    m_started = true;
    m_finished = false;

    ChangePhase(AIActionPhase::SelectCard);
}

//更新
void AIController::Update()
{
    if (!m_started || m_finished)
    {
        return;
    }

	//フェーズごとの処理
    switch (m_phase)
    {
    case AIActionPhase::SelectCard:
        UpdateSelectCard();
        break;

    case AIActionPhase::UseCard:
        UpdateUseCard();
        break;

    case AIActionPhase::SelectUnit:
        UpdateSelectUnit();
        break;

    case AIActionPhase::MoveUnit:
        UpdateMoveUnit();
        break;

    case AIActionPhase::DecideAttack:
        UpdateDecideAttack();
        break;

    case AIActionPhase::SelectTarget:
        UpdateSelectTarget();
        break;

    case AIActionPhase::Attack:
        UpdateAttack();
        break;

    case AIActionPhase::End:
        UpdateEnd();
        break;

    case AIActionPhase::None:
    default:
        break;
    }
}

// AI終了
void AIController::End()
{
    if (m_finished)
    {
        return;
    }

    m_phase = AIActionPhase::None;

    m_finished = true;
    m_started = false;
}

// リセット
void AIController::Reset()
{
    m_phase = AIActionPhase::None;

    m_started = false;
    m_finished = false;
}

// 完了フラグ
bool AIController::IsFinished() const
{
    return m_finished;
}

// AIが操作するプレイヤーを取得
BattlePlayer& AIController::GetAIPlayer()
{
    if (m_owner == UnitOwner::Player2)
    {
        return m_battleManager->GetPlayer2();
    }

    return m_battleManager->GetPlayer1();
}

// 現在のAIフェーズ取得
AIActionPhase AIController::GetPhase() const
{
    return m_phase;
}

// フェーズ変更
void AIController::ChangePhase(AIActionPhase phase)
{
    m_phase = phase;
}

// カード選択
void AIController::UpdateSelectCard()
{
    BattlePlayer& player = GetAIPlayer();

    // 手札がない場合はターン終了
    if (player.GetHand().GetCount() == 0)
    {
        ChangePhase(AIActionPhase::End);
        return;
    }

    // 今回は手札の0番目のカードを選択
    player.SelectCard(0);

    // 選択できたか確認
    if (player.GetSelectedCard() == nullptr)
    {
        ChangePhase(AIActionPhase::End);
        return;
    }

    ChangePhase(AIActionPhase::UseCard);
}

// カード使用
void AIController::UpdateUseCard()
{
    BattlePlayer& player = GetAIPlayer();

    // 選択中のカードを取得
    const CardInstance* selectedCard =
        player.GetSelectedCard();

    if (selectedCard == nullptr)
    {
        ChangePhase(AIActionPhase::End);
        return;
    }

    const CardData* cardData =
        selectedCard->GetCardData();

	// カードデータがない場合は終了
    if (cardData == nullptr)
    {
        ChangePhase(AIActionPhase::End);
        return;
    }

    // 現在はUnitカードだけ使用可能
    if (cardData->type != CardType::Unit)
    {
        player.ClearSelectedCard();
        ChangePhase(AIActionPhase::End);
        return;
    }

    // -------------------------
  // 敵陣の空いているマスを探す
  // -------------------------

    Board& board =
        m_battleManager->GetBoard();

    // Player2は下側から前進する想定なので、
    // 後ろ側から順番に配置場所を探す
    for (int y = BattleConfig::BOARD_HEIGHT - 1;
        y >= 0;
        --y)
    {
        for (int x = 0;
            x < BattleConfig::BOARD_WIDTH;
            ++x)
        {
            Cell* cell =
                board.GetCell(x, y);

            if (cell == nullptr)
            {
                continue;
            }

            // すでにユニットがいる場所は使わない
            if (cell->HasUnit())
            {
                continue;
            }

            // カード使用
            if (m_battleManager->UseSelectedCard(x, y))
            {
                ChangePhase(AIActionPhase::SelectUnit);
                return;
            }
        }
    }

    // 配置できる場所がなかった
    player.ClearSelectedCard();

    ChangePhase(AIActionPhase::End);
}
   
// ユニット選択
void AIController::UpdateSelectUnit()
{
    for (Unit* unit : m_battleManager->GetUnits())
    {
        if (unit == nullptr)
            continue;

        // 自分のユニット以外は無視
        if (unit->GetOwner() != m_owner)
            continue;

        // すでに行動済みのユニットは無視
        if (unit->HasActed())
            continue;

        // このユニットを選択
        m_battleManager->SelectUnit(unit);

        // 移動フェーズへ
        ChangePhase(AIActionPhase::MoveUnit);
        return;
    }

    // 行動できるユニットがいなかった
    ChangePhase(AIActionPhase::End);
}

// ユニット移動
void AIController::UpdateMoveUnit()
{
    // 選択中のユニットが存在するか確認
    const std::vector<Unit*>& units =
        m_battleManager->GetUnits();

    Unit* selectedUnit = nullptr;

    // AIが選択しているユニットを探す
    for (Unit* unit : units)
    {
        if (unit == nullptr)
        {
            continue;
        }

        if (unit->IsSelected())
        {
            selectedUnit = unit;
            break;
        }
    }

    // ユニットが見つからない場合
    if (selectedUnit == nullptr)
    {
        ChangePhase(AIActionPhase::DecideAttack);
        return;
    }

    // ユニットのカードデータ取得
    const CardData* cardData =
        selectedUnit->GetCardData();

    if (cardData == nullptr)
    {
        ChangePhase(AIActionPhase::DecideAttack);
        return;
    }

    // 移動パターン取得
    const std::vector<PatternOffset>& pattern =
        PatternDatabase::GetPattern(
            cardData->movePattern);

    // 移動パターンがない場合
    if (pattern.empty())
    {
        ChangePhase(AIActionPhase::DecideAttack);
        return;
    }

    // 移動可能なマスを保存
    std::vector<std::pair<int, int>> movableCells;


    Board& board =
        m_battleManager->GetBoard();

    int currentX = selectedUnit->GetBoardX();
    int currentY = selectedUnit->GetBoardY();

    // 移動パターンを調べる
    for (const PatternOffset& offset : pattern)
    {
        int offsetX = offset.x;
        int offsetY = offset.y;

        // Player2は前後方向を反転
        if (selectedUnit->GetOwner() == UnitOwner::Player2)
        {
            offsetY = -offsetY;
        }

        int targetX = currentX + offsetX;
        int targetY = currentY + offsetY;

        // 盤面外なら無視
        if (!board.IsInside(targetX, targetY))
        {
            continue;
        }

        Cell* targetCell =
            board.GetCell(targetX, targetY);

        if (targetCell == nullptr)
        {
            continue;
        }

        // すでにユニットがいる場所には移動しない
        if (targetCell->HasUnit())
        {
            continue;
        }

        // 移動可能なマスとして登録
        movableCells.push_back(
            std::make_pair(targetX, targetY));
    }

    // 移動できる場所がない場合
    if (movableCells.empty())
    {
        ChangePhase(AIActionPhase::DecideAttack);
        return;
    }

    // 移動可能な場所からランダムに1つ選択
    std::random_device rd;
    std::mt19937 randomEngine(rd());

    std::uniform_int_distribution<int> distribution(
        0,
        static_cast<int>(movableCells.size()) - 1);

    int randomIndex =
        distribution(randomEngine);

    int targetX =
        movableCells[randomIndex].first;

    int targetY =
        movableCells[randomIndex].second;

    // 実際に移動
    if (m_battleManager->MoveSelectedUnit(
        targetX,
        targetY))
    {
        // 移動成功
        ChangePhase(AIActionPhase::DecideAttack);
        return;
    }

    // 移動失敗
    ChangePhase(AIActionPhase::DecideAttack);
}

// 攻撃判断
void AIController::UpdateDecideAttack()
{
    // ここで攻撃するかどうかを判断する
    ChangePhase(AIActionPhase::SelectTarget);
}

// 攻撃対象選択
void AIController::UpdateSelectTarget()
{
    // ここで攻撃対象を決定する
    ChangePhase(AIActionPhase::Attack);
}

// 攻撃
void AIController::UpdateAttack()
{
    // ここで実際の攻撃処理を行う
    ChangePhase(AIActionPhase::End);
}

// ターン終了
void AIController::UpdateEnd()
{
    End();
}