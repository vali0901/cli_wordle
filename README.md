# CLI WORDLE

This is a command line interface game inspired by Wordle, in which you can either play the classic game, or you can play with the help from Wort, a bot that can suggest the best words you can guess depending on your game state.

Because it is a CLI game, there are no colored letters on the screen. Instead, I've used the following convention. When you type in a guess, you will get a pattern that will contain:
* `_` corresponding to a gray letter
* `[a-z]` corresponding to a yellow letter
* `[A-Z]` corresponding to a green letter

For example, if you guess the word `peach` and the pattern is `P_a__`, that means that the first letter of the word is `p` (green letter), the word also contains the letter `a` but not on the third position (yellow letter), and the leters `e c h` are not contained by the word (gray letters).

There are 3 modes in which you can play this game:

1. Classic Wordle game, without the help of Wort
2. Classic Wordle game, but at each guess Wort recommends the best 3 guesses possible
3. Getting Wort's help, here you can use Wort's suggestions to guess the word in other games of Wordle, you just type in your guess and the resulting pattern and Wort will have 3 suggestions for you

---
### Build and Run

Build: `make build` | `make`

Run: `make run`

---

Note that this game uses a limited number of words (contained in `words.txt`), these are the words Wort will work with. Other games of Wordle might have a larger dictionary.

