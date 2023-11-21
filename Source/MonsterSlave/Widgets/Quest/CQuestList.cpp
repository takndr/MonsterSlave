#include "Widgets/Quest/CQuestList.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Quest/CQuestData.h"

#include "Global.h"

void UCQuestList::NativeConstruct()
{
	Super::NativeConstruct();

	// ��ư ���ε�
	if (ListButton->OnClicked.IsBound() == false)
	{
		ListButton->OnClicked.AddDynamic(this, &UCQuestList::OnClickedListButton);
	}

	if (QuestData != nullptr)
	{
		QuestName->SetText(QuestData->Quest.QuestName);
	}
}

void UCQuestList::OnClickedListButton()
{
	if (OnClickedList.IsBound())
	{
		OnClickedList.Execute(QuestData);
	}
}
