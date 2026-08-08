---
title: Swiss Jass
subtitle: A simple introduction to Jass, the popular Swiss card game 
slug: 'jass'
date: 2026-08-07
---

Jass is a traditional card game that is widely played in Switzerland. It is a trick-taking game typically played with a deck of 36 cards by four players in two teams.

## Cultural Significance

Switzerland essentially consists of a mix of different cultures and influences, and has been established as a country not for its shared ancestry or language, but rather for political will and shared values. It is therefore even more interesting that there is a card game played throughout the country, with the same rules and same name (even if with various cards types: some influenced by German, others by French card games).

Jass has thus a cultural significance beyond the game itself, and is a tradition I find worth keeping alive.

## Basic Rules

There are many variations of Jass, so I will focus on the most common one, called "Schieber" (literally "pusher"), and will build an understanding from the foundation up so that you do not need to know the rules of similar trick-taking games as a prerequisite. The guide may therefore be a bit on the longer side as a trade-off for being more beginner-friendly.

I will try to follow the [official Jass rulebook 'Puur, Näll, As' by Göpf Egg and Albert Hagenbucher](https://shop.jassverzeichnis.ch/products/Offizielles-Jassreglement-nach-G%C3%B6pf-Egg-p214771111), but do not claim to be infallible. Please reach out to me if you find mistakes of any kind.

### Deck of Cards

Jass is usually played with a deck of 36 cards, either German-suited or French-suited.

In the following, we will assume a French-suited deck, which corresponds to the standard deck of cards used in many other card games such as Poker or Bridge. It is also the one used in the region I grew up in :). The cards are ranked from the highest ace on the left to the lowest 6 on the right, as demonstrated by the suit of hearts below:

{{<playing-card-row>}}
    {{<playing-card suit="heart" rank="ace" caption="1">}}
    {{<playing-card suit="heart" rank="king" caption="2">}}
    {{<playing-card suit="heart" rank="queen" caption="3">}}
    {{<playing-card suit="heart" rank="jack" caption="4">}}
    {{<playing-card suit="heart" rank="10" caption="5">}}
    {{<playing-card suit="heart" rank="9" caption="6">}}
    {{<playing-card suit="heart" rank="8" caption="7">}}
    {{<playing-card suit="heart" rank="7" caption="8">}}
    {{<playing-card suit="heart" rank="6" caption="9">}}
{{</playing-card-row>}}

### Trick-Taking Mechanics

As in most trick-taking mechanics, a _game_ ("Partie") is played in multiple rounds of _matches_ ("Spiel"), for which each player is dealt a hand of cards. Next, a match proceeds in rounds or "tricks", where each player lays down one card from their hand, while the player who played the highest card wins the trick and collects all cards on the table. In Jass, one trick is called a "Stich", literally translated to "stab".

The rules of evaluating the winning card of a trick contain the most complexity for beginners, so I will introduce them step by step.

The goal is to accumulate as many points as possible by winning cards in tricks. After a match, the cards are summed up and assigned points according to their rank and suit (see [Point System](#point-system) below). The player, or in Schieber the team, who reaches a pre-determined amount of points first wins the game.

### Distributing Cards

At the beginning of a match, a dealer is chosen. Since Jass is played in counter-clockwise order with the saying "der Ohrfeige entlang" (literally "along the slap"), the player sitting right of the assumingly right-handed dealer is called the "forehand" ("Vorhand"), and the player sitting on the left is called the "backhand" ("Rückhand").

There is one special oddity aimed at preventing the dealer from cheating: After the dealer shuffles the deck thoroughly, he/she places the deck in front of the player on their left (the backhand) to "cut" the deck (in German "Abheben"): Literally lift at least three cards off the top and place them next to the remaining deck. The dealer will then pick the decks up in reverse order to have a final mix-up from a player of the opposite team.

Only then will the cards be dealt to the players, again in counter-clockwise fashion, starting with the forehand and ending with the dealer. The cards are dealt in 3 rounds of 3 cards, so that each player ends up with a hand of 9 cards.

In the next play, the dealer role will be passed on to the next one in counter-clockwise order, likewise for the forehand and backhand.

### Trick Suit

The first player to lay down a card is the winner of the previous trick, or initially the forehand. He will determine the suit of the trick, which is the suit of the card he/she played.

All other players are obliged (called "Farbzwang") to play a card of the same suit if they have one (except for trump cards, which we'll deal with in the next section). Within a suit the normal ranking of card applies, so that e.g., a 10 of hearts will beat a 9 of hearts but lose to a queen of hearts. If a player is unable to match the suit of the trick, he/she may play any other card, which will however lose to all cards of the trick suit.

Here are a few examples of tricks, where the first card and winner are written above and below the cards:

{{<playing-card-row>}}
    {{<playing-card suit="diamond" rank="6" captionAbove="first card" caption="winner">}}
    {{<playing-card suit="heart" rank="6">}}
    {{<playing-card suit="club" rank="6">}}
    {{<playing-card suit="spade" rank="6">}}
{{</playing-card-row>}}

---

{{<playing-card-row>}}
    {{<playing-card suit="heart" rank="9">}}
    {{<playing-card suit="heart" rank="10" captionAbove="first card">}}
    {{<playing-card suit="heart" rank="king">}}
    {{<playing-card suit="heart" rank="ace" caption="winner">}}
{{</playing-card-row>}}

---

{{<playing-card-row>}}
    {{<playing-card suit="spade" rank="10">}}
    {{<playing-card suit="spade" rank="jack" captionAbove="first card">}}
    {{<playing-card suit="spade" rank="queen" caption="winner">}}
    {{<playing-card suit="heart" rank="ace">}}
{{</playing-card-row>}}

The suit obligation rule makes for an interesting strategic element: In the beginning it is easy to match the suit of the trick, but as the match progresses and cards dwindle, it gets increasingly more difficult to match the trick suit. Being able to choose the suit of the trick is therefore a powerful advantage because you can force opponents to lose valuable cards against lower ranks, particularly towards the end of a play.

### Trump

There is another element to the game that adds a twist: The trump suit.

In the Schieber and most other variants, a match (meaning a round of 9 tricks) has a dedicated _trump suit_, which wins over all other suits regardless of the card rank or the suit of the trick.

A trump card can be played by any players on any turn, even by the first player of the trick (which would make the trick suit the same as the trump suit). If a player plays a trump card into a trick with a different suit, it is called _stabbing in_ ("einstechen").

The following players are not required to also play a trump card (unless trump suit = trick suit), but will lose the trick if they do not. Players however _must not_ play a lower trump card ("under trumping" / "untertrumpfen"), unless they have only trump cards left in their hand.

{{<playing-card-row>}}
    {{<playing-card suit="spade" rank="10">}}
    {{<playing-card suit="spade" rank="jack" captionAbove="first card">}}
    {{<playing-card suit="spade" rank="queen">}}
    {{<playing-card suit="heart" rank="ace" caption="winner" captionAbove="trump">}}
{{</playing-card-row>}}

---

{{<playing-card-row>}}
    {{<playing-card suit="diamond" rank="jack" caption="winner" captionAbove="trump">}}
    {{<playing-card suit="diamond" rank="10" captionAbove="first card & trump">}}
    {{<playing-card suit="spade" rank="king">}}
    {{<playing-card suit="diamond" rank="8" captionAbove="trump">}}
{{</playing-card-row>}}


Interestingly the _trump jack_ and the _trump nine_ (also "Näll") are more powerful than the others, which makes them the most valuable cards in the game. This results in a different ranking of the trump suit than for non-trump suits:

{{<playing-card-row>}}
    {{<playing-card suit="club" rank="jack" caption="1">}}
    {{<playing-card suit="club" rank="9" caption="2">}}
    {{<playing-card suit="club" rank="ace" caption="3">}}
    {{<playing-card suit="club" rank="king" caption="4">}}
    {{<playing-card suit="club" rank="queen" caption="5">}}
    {{<playing-card suit="club" rank="10" caption="6">}}
    {{<playing-card suit="club" rank="8" caption="7">}}
    {{<playing-card suit="club" rank="7" caption="8">}}
    {{<playing-card suit="club" rank="6" caption="9">}}
{{</playing-card-row>}}

Some example tricks where these new rules come into play:

{{<playing-card-row>}}
    {{<playing-card suit="heart" rank="ace" captionAbove="trump">}}
    {{<playing-card suit="heart" rank="king" captionAbove="trump">}}
    {{<playing-card suit="heart" rank="7" captionAbove="trump">}}
    {{<playing-card suit="heart" rank="jack" caption="winner" captionAbove="trump">}}
{{</playing-card-row>}}

---

{{<playing-card-row>}}
    {{<playing-card suit="spade" rank="ace" captionAbove="trump">}}
    {{<playing-card suit="club" rank="ace">}}
    {{<playing-card suit="club" rank="king" captionAbove="first card">}}
    {{<playing-card suit="spade" rank="9" caption="winner" captionAbove="trump">}}
{{</playing-card-row>}}

---

{{<playing-card-row>}}
    {{<playing-card suit="diamond" rank="king" captionAbove="first card">}}
    {{<playing-card suit="club" rank="6" captionAbove="trump" caption="winner">}}
    {{<playing-card suit="diamond" rank="queen">}}
    {{<playing-card suit="diamond" rank="ace" >}}
{{</playing-card-row>}}

As the trump cards are the most valuable ones, it is important to determine when to play them wisely. It is also advisable to keep track of the trump cards that have already been played, as you can easily lose high scoring cards to a trump card.

Besides the four suits, there are two additional trump options that can be chosen:

- Top-Down (also "Obenabe"), where there is basically no trump suit and the cards are ranked from ace down to 6 in all suits.
- Bottom-Up (also "Undenufe"), where the cards are ranked in reverse order from 6 up to ace in all suits. While the 6 and ace also swap their point values, the other rank point values remain and are not reversed! So, e.g., the 7 is still worth 0 points, but is the second-highest card in the game.

### Team Play & Trump Determination

How a trump suit is determined depends heavily on the variant of Jass being played. Since we are just looking at the Schieber here, we solely will focus on the rules for this variant. It is interlinked with the team play which we also haven't discussed yet in more detail, which we'll do now as well.

Although each trick can be won by a single player, the game is played by two teams of two players. The players are not allowed to tell each other which cards they have, or even if they have generally good or bad cards. This is considered cheating and would undermine some mechanics.

To make direct communication more difficult, players of a team are required to sit opposite of each other, or around a table, player from different teams alternate.

<table style="margin: 0 auto; width: auto; display: table; border-collapse: unset; text-align: center">
    <tr style="background: none"><td></td><td>Team 1</td><td></td></tr>
    <tr style="background: none"><td>Team 2</td><td><b>Table</b></td><td>Team 2</td></tr>
    <tr style="background: none"><td></td><td>Team 1</td><td></td></tr>
</table>

The Schieber Jass makes use of this non-communication rule in a clever way: The forehand is given the opportunity to choose the trump suit after looking at his/her cards, but is also allowed to _pass_ ("push" or "schieben") the choice to his companion on the opposite side of the table. Once the choice has been passed on, the companion must choose one of the six trump options.

There is no foolproof strategy here: Look if you have a sufficiently strong suit on your hands, and if not, pass the choice to your companion and hope that he/she has a better hand. 

### Point System

After all tricks of a match have been played, the cards are collected and awarded points according to their rank and suit. The chosen trump has significance here:

**Non-Trump suits** given that another suit is chosen as trump:

{{<playing-card-row>}}
    {{<playing-card suit="heart" rank="ace" caption="`11P`">}}
    {{<playing-card suit="heart" rank="king" caption="`4P`">}}
    {{<playing-card suit="heart" rank="queen" caption="`3P`">}}
    {{<playing-card suit="heart" rank="jack" caption="`2P`">}}
    {{<playing-card suit="heart" rank="10" caption="`10P`">}}
    {{<playing-card suit="heart" rank="9" caption="`0P`">}}
    {{<playing-card suit="heart" rank="8" caption="`0P`">}}
    {{<playing-card suit="heart" rank="7" caption="`0P`">}}
    {{<playing-card suit="heart" rank="6" caption="`0P`">}}
{{</playing-card-row>}}

The interesting part here is that the 10 is worth more points than a king, queen, and jack combined, but is still ranked lower in terms of winning a trick. So a 10 is usually hard to get home, but also a good hunting target for opponents.

**Trump suit:**

{{<playing-card-row>}}
    {{<playing-card suit="club" rank="jack" caption="`20P`">}}
    {{<playing-card suit="club" rank="9" caption="`14P`">}}
    {{<playing-card suit="club" rank="ace" caption="`11P`">}}
    {{<playing-card suit="club" rank="king" caption="`4P`">}}
    {{<playing-card suit="club" rank="queen" caption="`3P`">}}
    {{<playing-card suit="club" rank="10" caption="`10P`">}}
    {{<playing-card suit="club" rank="8" caption="`0P`">}}
    {{<playing-card suit="club" rank="7" caption="`0P`">}}
    {{<playing-card suit="club" rank="6" caption="`0P`">}}
{{</playing-card-row>}}

Notice how the trump jack and nine are worth significantly more points than the other cards, meaning that they are not only strong in winning tricks, but also in scoring points.

**Top-Down** ("Obenabe") for all suits:

{{<playing-card-row>}}
    {{<playing-card suit="diamond" rank="ace" caption="`11P`">}}
    {{<playing-card suit="diamond" rank="king" caption="`4P`">}}
    {{<playing-card suit="diamond" rank="queen" caption="`3P`">}}
    {{<playing-card suit="diamond" rank="jack" caption="`2P`">}}
    {{<playing-card suit="diamond" rank="10" caption="`10P`">}}
    {{<playing-card suit="diamond" rank="9" caption="`0P`">}}
    {{<playing-card suit="diamond" rank="8" caption="`8P`">}}
    {{<playing-card suit="diamond" rank="7" caption="`0P`">}}
    {{<playing-card suit="diamond" rank="6" caption="`0P`">}}
{{</playing-card-row>}}

Since there are no trump cards in these two variants, the remaining points are distributed among the 8, which now counts as much as its face value.

**Bottom-Up** ("Undenufe") for all suits:

{{<playing-card-row>}}
    {{<playing-card suit="spade" rank="ace" caption="`0P`">}}
    {{<playing-card suit="spade" rank="king" caption="`4P`">}}
    {{<playing-card suit="spade" rank="queen" caption="`3P`">}}
    {{<playing-card suit="spade" rank="jack" caption="`2P`">}}
    {{<playing-card suit="spade" rank="10" caption="`10P`">}}
    {{<playing-card suit="spade" rank="9" caption="`0P`">}}
    {{<playing-card suit="spade" rank="8" caption="`8P`">}}
    {{<playing-card suit="spade" rank="7" caption="`0P`">}}
    {{<playing-card suit="spade" rank="6" caption="`11P`">}}
{{</playing-card-row>}}

Similarly to the top-down variant, the 8 now counts as its face value. In addition, the 6 and ace have swapped their positions to `11` and `0` respectively, so that the 6 is now the highest card in the game both in terms of winning a trick and scoring points. The other cards however remain the same as in the top-down variant.

**Last Trick**

The team that wins the last trick of a match is awarded an additional 5 points.

**Control**

The total amount of points in a match is always `157` (`152` plus `5` for the last trick), regardless of the chosen trump suit. This can be used as a cross-check after all cards have been counted.

### Thanking & Winning the Game

The players determine before the game starts how many points are required to win the game. Usually, a game is played somewhere from `1000` to `2500` in `500` increments.

It is customary to end the game by thanking the losing team for the game through a handshake.

You don't even have to finish a match: Once you reach the required amount of points, you can stop the game early and declare victory by thanking the opponents. This may be important in close calls. If you however thank _too early_, you will lose the game even if you have more points in total, so be careful.

---

Attribution for these great illustrations goes to Chris Aguilar:

```
Vectorized Playing Cards 3.2
https://totalnonsense.com/open-source-vector-playing-cards/
Copyright 2011,2024 – Chris Aguilar – conjurenation@gmail.com
Licensed under: LGPL 3.0 - https://www.gnu.org/licenses/lgpl-3.0.html
```
