#include "Deck.h"



Deck::Deck()
{
    this->DeckCards = new BaseStack<Card*>();
}


Deck::~Deck()
{
    //this->DeckCards->Release();

    delete(this->DeckCards);
}

void Deck::SetupStandard52CardsDeck()
{
    for (int i = 0; i < Card::CARD_SUITS_COUNT; i++)
    {
        for (int k = 0; k < Card::CARD_VALUE_COUNT; k++)
        {
            Card* newCard = new Card();

            newCard->CardSuit = (Card::CARD_SUITS)i;
            newCard->CardValue = (Card::CARD_VALUE)k;

            this->DeckCards->Push(newCard);
        }
    }
}

void Deck::ShuffleDeck()
{
    this->DeckCards->Shuffle();
}

Card* Deck::DrawCard()
{
    Card* drawn = this->DeckCards->Pop();

    return drawn;
}
