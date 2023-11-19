#include "Widgets/Quest/CQuestList.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Global.h"

void UCQuestList::NativeConstruct()
{
	Super::NativeConstruct();

	// ��ư ���ε�
	if (ListButton->OnClicked.IsBound() == false)
	{
		ListButton->OnClicked.AddDynamic(this, &UCQuestList::OnClickedListButton);
	}

	if (Quest != nullptr)
	{
		QuestName->SetText(Quest->GetQuestInfo().QuestName);
	}
}

void UCQuestList::OnClickedListButton()
{
	if (OnClickedList.IsBound())
	{
		OnClickedList.Execute(Quest);
	}
}
