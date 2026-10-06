#include "AIController.h"

//battleマネージャー
#include "../BattleManager.h"

//プレイヤー
#include "../Player/BattlePlayer.h"

#include "../BattleConfig.h"
#include "../board/Board.h"
#include "../board/Cell/Cell.h"

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

    // 選択中のカードを取得
    const CardInstance* selectedCard =
        player.GetSelectedCard();

    // カードが選択されていない場合
    if (selectedCard == nullptr)
    {
        ChangePhase(AIActionPhase::End);
        return;
    }

    // 元カードデータを取得
    const CardData* cardData =
        selectedCard->GetCardData();

    if (cardData == nullptr)
    {
        player.ClearSelectedCard();

        ChangePhase(AIActionPhase::End);
        return;
    }

    // 現段階ではUnitカードだけ使用する
    if (cardData->type != CardType::Unit)
    {
        player.ClearSelectedCard();

        ChangePhase(AIActionPhase::End);
        return;
    }

    // 敵側から空いているマスを探す
    for (int y = BattleConfig::BOARD_HEIGHT - 1; y >= 0; --y)
    {
        for (int x = 0; x < BattleConfig::BOARD_WIDTH; ++x)
        {
            Cell* cell =
                m_battleManager->GetBoard().GetCell(x, y);

            if (cell == nullptr)
            {
                continue;
            }

            // 空いているマスならカードを使用
            if (!cell->HasUnit())
            {
                if (m_battleManager->UseSelectedCard(x, y))
                {
                    ChangePhase(AIActionPhase::SelectUnit);
                    return;
                }
            }
        }
    }

    // 手札がない場合はターン終了
}

// カード使用
void AIController::UpdateUseCard()
{
    // ここで実際のカード使用処理を後ほど実装する
    ChangePhase(AIActionPhase::SelectUnit);
}

// ユニット選択
void AIController::UpdateSelectUnit()
{
    // ここで行動可能なユニットを探す
    ChangePhase(AIActionPhase::MoveUnit);
}

// ユニット移動
void AIController::UpdateMoveUnit()
{
    // ここで移動先を決定する
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