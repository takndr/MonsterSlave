> **퀘스트 구성<br>**
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
>
>
>
>
>
>
>
>
>
>
>
> 플레이어 퀘스트 위젯, NPC 퀘스트 위젯
> * [퀘스트 구성]