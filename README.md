# connect4 bot
## Download:
```
git clone 'https://github.com/tokox/connect4-bot.git'
```
## Compile:
```
cd connect4-bot
make connect4-bot
```
## Run:
```
./connect4-bot
```
## Arguments:
- `help` - print this file if exists in working directory, else print link to this file on github and exit
- `start` - engine to start the game. Default: no.
- `print_moves` - print engine moves on error output; made for gui or engine battles. Default: no
- `history` - preserve previous board states on output. Default: no
- `depth [any number]` - depth of the engine. Default: none.
- `time [any number]` - time for the engine. Default: 5. *When used, depth is set to `time/~one_depth_time`. With `depth` depth is set to `min(depth, time/~one_depth_time)`. Estimated. May be inaccurate*
- **:TODO:** `X|O` - which one is engine playing. Default: O
- **:TODO:** `position [position]` - position to start the game. **No validation**
- **:TODO:** `moves [1-7]+` - moves already played in the game. **Validation**

## TODO:
- `position`, `moves` and `X|O` arguments
- `Ctrl+C` stops computer thinking; infinite analysis
- make bot play random best move instead of last one
