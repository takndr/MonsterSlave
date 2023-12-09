## 퀘스트

### 퀘스트 구성
> ```
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	int32 QuestID;
> 
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	EQuestType QuestType;
> 
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	EQuestProgressType QuestProgress;
> 
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	FText QuestName;
> 
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	FText QuestConversation;
> 
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	TSubclassOf<AActor> QuestObjectives;
> 
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	uint8 QuestNums;
> 
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	uint8 CurrentCount;
> 
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	TArray<class UCItemData*> GiftDatas;
> 
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	class UCQuestData* NextQuest;
> ```
> * QuestID : 퀘스트의 고유 ID<br>
> * QuestType : 퀘스트 내용이 어떤 타입인지<br>
> * QuestProgress : 퀘스트의 현재 진행 상황<br>
> * QuestName : 퀘스트의 이름<br>
> * QuestConversation : 퀘스트 수락 시, NPC와의 대화 내용<br>
> * QuestObjectives : 퀘스트 클리어를 위한 목표<br>
> * QuestNums : 퀘스트 클리어를 위한 목표의 개수<br>
> * CurrentCount : 현재 목표를 몇개(명)까지 진행하였는지 확인<br>
> * GiftDatas : 플레이어가 퀘스트를 완료하였을 때, 받을 수 있는 보상<br>
> * NextQuest : 현재 퀘스트를 완료하였을 때, 이후 연계되는 퀘스트<br>
>

### 퀘스트 진행
> 퀘스트를 가지고 있는 NPC가 있고, 플레이어가 퀘스트를 진행할 수 있는 상태라면 해당 NPC위의 '!'마크를 통해 현재 수락할 수 있는 퀘스트가 있다는 것을 확인할 수 있습니다.<br>
> ![QuestAcceptable](https://github.com/takndr/MonsterSlave/assets/126765215/506e0918-7c09-4025-abb6-e4adad760514)<br>
> 퀘스트의 진행 상황은 총 5가지로 각각 UnAvailable, Available, InProgress, Completed, Clear 로 구성되어 있습니다.<br>
> (UnAvailable과 Clear일 경우에는 맵에서 확인이 불가합니다.)<br>
> ![Quest1](https://github.com/takndr/MonsterSlave/assets/126765215/2105c903-5e1a-4746-9911-81f2e291a3b7)
> ![Quest2](https://github.com/takndr/MonsterSlave/assets/126765215/312a17e9-67e4-46c8-af02-1301df4f380d)
> ![Quest3](https://github.com/takndr/MonsterSlave/assets/126765215/4468dd5f-7200-4639-b572-06cdece141d0)<br>
> 이후 퀘스트의 목표를 달성하게 되면 '!'였던 마크가 '?'로 바뀌게 되며, 퀘스트의 목표를 달성하였다는 것을 맵에서 확인할 수 있습니다.<br>
> ![QuestClear](https://github.com/takndr/MonsterSlave/assets/126765215/dfd8ddf7-76db-4df6-a67e-088355a84aa5)<br>
> 또는 'P'키를 눌러 현재 어떤 퀘스트를 진행하고 있는지 확인할 수 있으며, 진행상황이 어떠한지도 확인이 가능합니다.<br>
> ![QuestLog1](https://github.com/takndr/MonsterSlave/assets/126765215/b744c242-3572-4d45-a85c-4a2b51ed2338)
> ![QuestLog2](https://github.com/takndr/MonsterSlave/assets/126765215/55f0d4e7-65c9-4de4-aa91-703b5295a60d)<br>

### 퀘스트 관리
> * SaveGame을 통하여 저장을 할 때, NPC들이 퀘스트를 편하게 관리할 수 있는<br>QuestComponent에서 Save에 관련된 함수에 바인딩을 진행하였습니다.<br>
> * 만약에 이전에 저장을 했던 데이터가 있다면, 저장된 퀘스트에서 동일한 목록이 있는지 확인하고<br>있다면 기존에 있던 데이터를 덮어 씌우고, 없다면 새로이 추가로 작성하였습니다.<br>
> ```
> int index = saveGame->AllQuests.Find(Quest);
> 
> if (index == INDEX_NONE)
> {
> 	saveGame->AllQuests.AddUnique(Quest);
> }
> else
> {
> 	saveGame->AllQuests[index] = Quest;
> }
> ```