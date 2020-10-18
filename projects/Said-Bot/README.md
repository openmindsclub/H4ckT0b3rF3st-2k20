##Said-BOT

Welcome to Said-BOT, the only bad chess bot.
This bot has been conceived as a way to give anyone a (shaky) platform to build
their own chess bot, as well as teaching myself how to make a chess "engine".
So far, this chess engine is absolutely not the next stockfish, but it is a good
demonstration on how you can use python-chess in order to make this bot.

### Used Libraries / Frameworks

* chess (also called python-chess)
* SVG
* datetime

### A short chess introduction.
In order to understand how a chess engine works, you need to understand how
chess works, and for that, it's gonna take a lot of time to learn everything
fortunately, i can recommend you some good chess content for you to learn new
things, ideas or even just getting better at chess.

#### Chess websites
* [Lichess](https://www.lichess.org)   : a chess website that is both open source,
free and awesome, frequently used by grand masters, has a lot ofchess-related
content like simple tutorials and an analysis engine that helps you play better.

* [Chess.com](https://www.chess.com) : another chess website, who generally
speaking has the best players (excluding the current world champion because he
has his own website lol), it's the website i play the most on.

### How it works.
To put it simply, this chess engine uses a minmax algorithm called alphabeta prunning
which basically always look for the 2 best moves it can find (alpha and beta)
based on a depth of search and select one of them based on its evaluation.

The evaluation of the board is based on pretty standard rating : each piece has its
own rate, as well as it's position on the board, excluding the king, here is how each
piece is rated:
Pawn : 100
knight and bishop : 300
Rook : 600
Queen : 900
Some example of good positions : you often keep bishops in open diagonals like
snipers, The knights will prefer more central positions, as the saying goes, knight
on the rim is grim...etc

To supplement the alphabeta we add a quiescense algorithm, which checks for every
possible capture move.
By keeping in history each moves, the engine will be able to select at each move
the best possible one and, we hope, manage to checkmate the opponent.

The first couple of moves a chess player makes is called an opening, some of them
are good (i personally love the guiocco pianissimo(white) and the king's indian defense(black))
In order to emulate that, we're gonna give the chess engine an opening book, which is basically a
pgn of chess matches, once the engine doesn't find a move in its book, it will rely on the
alphabeta prunning to decide the next best move.

### Why making a chess-bot and not just ripping stockfish?
Because i can and you're asking too many questions.

### Will i make a tutorial on how to play chess?
Who do you think i am? a good chess player? please i can't even play blindfold
chess so please find a better player than me please.

(If there is a demand, i'll make a simple chess tutorial)

### Contributions.
TBA i'm not sure for now.
