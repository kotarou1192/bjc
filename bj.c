#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>


struct card {
  char name[128];
  int num;
  bool isDrawn;
};

struct cardType {
  char name[128];
};

void createNewDeck(struct card* cards, struct cardType* cardtype, size_t length) {

  int cardNumber = 0;
  for(size_t num = 0; num < length; num++){
    for(int i = 1; i < 14; i++){
      cards[cardNumber].num = i;
      cards[cardNumber].isDrawn = false;
      // printf("%d\n", cardNumber);
      // printf("%s\n", cardtype[num].name);
      strcpy(cards[cardNumber].name, cardtype[num].name);
      cardNumber++;
    }
  }
}

struct card* drawCard(struct card* deck, size_t deckSize, int randomNumber){
  if (randomNumber >= deckSize){
    do
    {
      randomNumber--;
      if (randomNumber == -1) return NULL;
    } while (deck[randomNumber].isDrawn == true);
    deck[randomNumber].isDrawn = true;
    return &deck[randomNumber];
  }
  if (deck[randomNumber].isDrawn == false){
    deck[randomNumber].isDrawn = true;
    return &deck[randomNumber];
  }
  if (deck[randomNumber].isDrawn == true){
    return drawCard(deck, deckSize, randomNumber + 1);
  }
}

bool isContinue(){
  char input[1024];
  printf("draw card? [y/n]\n");
  scanf("%s", input);

  if (strcmp("y", input) == 0){
    return true;
  } else if(strcmp("n", input) == 0) {
    return false;
  } else {
    printf("try agein");
    isContinue();
  }
}

int addScore(int total, int now){
  if(now > 10){
    now = 10;
  }
  total += now;
  return total;
}

void playGame(){
  struct card deck[52];
  size_t deckSize = sizeof(deck) / sizeof(deck[0]);
  struct cardType name[] = {"heart", "spade", "diamond", "club"};
  createNewDeck(deck, name, sizeof(name) / sizeof(struct cardType));

  int dealerScore = 0;
  int playerScore = 0;

  struct card* dealer;
  dealer = drawCard(deck, deckSize, rand() % 52);
  dealerScore = addScore(dealerScore, (*dealer).num);
  printf("dealer -- %s:%d\n", (*dealer).name, (*dealer).num);
  dealer = drawCard(deck, deckSize, rand() % 52);
  dealerScore = addScore(dealerScore, (*dealer).num);

  struct card* drawn;

  for(int i = 0; i < 2; i++){
    drawn = drawCard(deck, deckSize, rand() % 52);
    printf("you -- %s:%d\n", (*drawn).name, (*drawn).num);
    playerScore = addScore(playerScore,(*drawn).num);
  }

  printf("now your score: %d\n", playerScore);

  while (isContinue()){
    drawn = drawCard(deck, deckSize, rand() % 52);
    if(drawn == NULL) break;
    printf("you -- %s:%d\n", (*drawn).name, (*drawn).num);
    playerScore = addScore(playerScore, (*drawn).num);
    printf("now your score: %d\n", playerScore);
    if (playerScore > 21){
      printf("score burst! YOU LOSE");
      return;
    }
  }

  printf("dealer -- %s:%d\n", (*dealer).name, (*dealer).num);

  while (dealerScore <= 17){
    dealer = drawCard(deck, deckSize, rand() % 52);
    printf("dealer -- %s:%d\n", (*dealer).name, (*dealer).num);
    dealerScore = addScore(dealerScore, (*dealer).num);
  }

  if(dealerScore > 21){
    printf("dealer score : %d\n", dealerScore);
    printf("your score : %d\n", playerScore);
    printf("score burst! dealer lose");
    return;
  } else if(dealerScore > playerScore) {
    printf("dealer score : %d\n", dealerScore);
    printf("your score : %d\n", playerScore);
    printf("dealer win!");
    return;
  } else if(playerScore > dealerScore) {
    printf("dealer score : %d\n", dealerScore);
    printf("your score : %d\n", playerScore);
    printf("player win!");
    return;
  } else {
    printf("draw");
  }
}

int main(void) {
  srand((unsigned)time(0UL));
  char input[1024];
  printf("play game? [y/n]\n");
  scanf("%s", input);

  if (strcmp("y", input) == 0){
    printf("start!\n");
    playGame();
  } else {
    printf("bye");
    return 0;
  }

  return 0;
}

