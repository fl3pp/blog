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

There are many variations of Jass, so I will focus on the most common one, called "Schieber" (literally "pusher"), and will build an understanding from the foundation up so that you do not need to know the rules of similar trick-tacking games as a prerequisite. The guide may therefore be a bit on the longer side as a trade-off for being more beginner-friendly.

I will try to follow the [official rulebook by Göpf Egg and Albert Hagenbucher](https://shop.jassverzeichnis.ch/products/Offizielles-Jassreglement-nach-G%C3%B6pf-Egg-p214771111), but do not claim to be infallible.

### Deck of Cards

Jass is usually played with a deck of 36 cards, either German-suited or French-suited.

In the following, we will assume a French-suited deck, which corresponds to the standard deck of cards used in many other card games such as Poker or Bridge. It is also the one used in the region I grew up in :). The cards are ranked from the highest ace on the left to the lowest 6 on the right, as demonstrated by the suite of hearts below:

{{<playing-card-row>}}
    {{<playing-card suite="heart" rank="ace" caption="1">}}
    {{<playing-card suite="heart" rank="king" caption="2">}}
    {{<playing-card suite="heart" rank="queen" caption="3">}}
    {{<playing-card suite="heart" rank="jack" caption="4">}}
    {{<playing-card suite="heart" rank="10" caption="5">}}
    {{<playing-card suite="heart" rank="9" caption="6">}}
    {{<playing-card suite="heart" rank="8" caption="7">}}
    {{<playing-card suite="heart" rank="7" caption="8">}}
    {{<playing-card suite="heart" rank="6" caption="9">}}
{{</playing-card-row>}}

### Trick-Taking Mechanics

As in most trick-taking games each player is dealt a hand of cards at the beginning of a play. Next, the game proceeds in rounds or "tricks", where each player lays down one card from their hand, while the player who played the highest card wins the trick and collects all cards on the table. In Jass, one trick is called a "Stich", literally translated to "stab".

The rules of evaluating the card winner contain the most complexity for beginners, so I will introduce them to you step by step in the following sections.

The goal is to accumulate as many points as possible by winning cards through stabs. In the end, the cards are summed up and assigned points according to their rank and suite (see [Point System](#point-system) below). The player, or in Schieber the team, with the most points at the end wins the game.

### Distributing Cards

At the beginning of a game, a dealer is chosen. Since Jass is played in counter-clockwise order with the saying "der Schwinte entlang" (literally "along the slap"), the player sitting right of the assumingly right-handed dealer is called the "forehand" ("Vorhand"), and the player sitting on the left is called the "backhand" ("Rückhand").

There is one special oddity aimed at preventing the dealer from cheating: After the dealer shuffles the deck thoroughly, he/she places the deck in front of the player on their left (the backhand) to "cut" the deck (in German "Abheben"): Literally lift at least three cards off the top and place them next to the remaining deck. The dealer will then pick the decks up in reverse order to have a final mix-up from a player of the opposite team.

Only then will the cards be dealt to the players, again in counter-clockwise fashion, starting with the forehand and ending with the dealer. The cards are dealt in 3 rounds of 3 cards, so that each player ends up with a hand of 9 cards.

In the next play, the dealer role will be passed on to the next one in counter-clockwise order, likewise for the forehand and backhand.

### Stab Suite

The first player to lay down a card first is the winner of the previous stab, or initially the forehand. He will determine the suite of the stab, which is the suite of the card he/she played.

All other players are obliged (called "Farbzwang") to play a card of the same suite if they have one. Within a suite the normal ranking of card applies, so that e.g., a 10 of hearts will beat a 9 of hearts but lose to a queen of hearts. If a player is unable to match the suite of the stab, he/she may play any other card, which will however lose to all cards of the stab suite.

Here are a few examples of stabs, where the first card and winner are written above and below the cards:

{{<playing-card-row>}}
    {{<playing-card suite="diamond" rank="6" captionAbove="first card" caption="winner">}}
    {{<playing-card suite="heart" rank="6">}}
    {{<playing-card suite="club" rank="6">}}
    {{<playing-card suite="spade" rank="6">}}
{{</playing-card-row>}}

---

{{<playing-card-row>}}
    {{<playing-card suite="heart" rank="9">}}
    {{<playing-card suite="heart" rank="10" captionAbove="first card">}}
    {{<playing-card suite="heart" rank="king">}}
    {{<playing-card suite="heart" rank="ace" caption="winner">}}
{{</playing-card-row>}}

---

{{<playing-card-row>}}
    {{<playing-card suite="spade" rank="10">}}
    {{<playing-card suite="spade" rank="jack" captionAbove="first card">}}
    {{<playing-card suite="spade" rank="queen" caption="winner">}}
    {{<playing-card suite="heart" rank="ace">}}
{{</playing-card-row>}}


The suite obligation rule makes for an interesting strategic element: In the beginning it is easy to match the suite of the stab, but as the game progresses and cards dwindle, it gets increasingly more difficult to match the stab suite. Being able to choose the suite of the stab is therefore a powerful advantage because you can force opponents to lose valuable cards against lower ranks, particularly towards the end of a play.


### Trump

### Point System

### Summarized Process

## Basic Strategies

Card Counting