# Blackjack Final

<h2>Introduction</h2>
 Blackjack, also known as twenty-one, is a card game where one or more players compare their cards against the dealer. It is played with at least one deck of cards. The objective of the game is to beat the dealer in one of the following ways:
 
<ul>
 <li>Their hand is worth twenty-one points (called a blackjack) when they draw their first two cards</li>
 <li>Reach a final score that's higher than the dealer without exceeding twenty-one points</li>
 <li>Let the dealer exceed twenty-one points when they hit additional cards (the dealer busts)</li>
</ul>

Each player is dealt two cards. The dealer is also dealt two cards, but one of them is face down. All of the numbered cards are worth their pip value. Face cards (Jack, King, & Queen) are worth 10 points. Ace cards are worth 11 points. The players are allowed to draw additional cards to increase their hand's value, but they are eliminated from the game if their hand exceeds 21 points (they bust). 

Once all of the players complete their hands. It's the dealer's turn. The dealer does not complete their hand if all of the players had either busted or recieved blackjacks. Like the players, the dealer can choose to add cards to their hand or stay.

The players win by getting a blackjack without the dealer getting one, not busting but having a hand worth more than the dealer, or not busting but having the dealer bust.


<h2>Summary</h2>
<ul>
 <li>Project Size: > 750 lines</li>
 <li>Utilizes the STL libarary by creating a list of players, stack of cards, a map of card names</li>
 <li>Players are iterated through multiple times for them to create their account, and add a wager</li>
 <li>In the end, algorithm is used to swap players into their order by lowest-to-highest score</li>
 <li>Recursion is used once to iterate through the list of players</li>
 <li>A recursive sort is used to sort players by score</li>
 <li>A tree and tree traversals are used to create a card deck</li>
</ul>
