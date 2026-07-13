# Chess Clone – WMM

## 1\. World – domain assumptions

1) ### The chess domain (rules)

- **W-C1.** The rules of chess are fixed and unambiguous. Given a position and a move, the move is either legal or not; given a position, its game-theoretic status (in-progress / checkmate / one of the draw conditions) is determined.  
- **W-C2.** A chess *position* is fully captured by: piece placement, side to move, castling rights, en passant target, half-move clock, and full-move counter. (This is exactly the information in a FEN record.)  
- **W-C3.** Threefold repetition is defined over the *repeatable* part of the position (placement \+ side to move \+ castling \+ en passant availability), not the move clocks.

2) ### The human user

- **W-U1.** The user can read the rendered board and text output and react to it.  
- **W-U2.** The user may express an *illegal* intention (drag to an illegal square). The world does not prevent this; the program must.

3) ### The engine (Stockfish / any UCI engine)

*Grounded in the Stockfish 18 / UCI documentation.*

- **W-E1.** Given a position, the engine can search it and report an evaluation and a recommended move; the longer it is given to search, the more reliable the evaluation and recommendation tend to be.  
- **W-E2.** Stockfish's playing strength can be limited below its maximum in two ways: a skill-level setting on a 0–20 scale (lower is weaker), or a target-rating mode which, once enabled, overrides the skill-level setting and aims for an Elo target within Stockfish's supported range (roughly 1320–3190, as of Stockfish 18).  
- **W-E3.** The engine can be asked for more than one candidate line from a position (up to a documented maximum of 256), not only the single best.  
- **W-E4.** The engine can evaluate any arbitrary legal position.  
- **W-E5.** The engine runs as a separate, independent process.

4) ### W-P – The host platform

- **W-P1.** A monotonic wall clock is available for measuring elapsed time (needed for time controls).

## 2\. Requirements (R)

1) ### Play against the engine

- **R-A1.** The user can start a new game in which one side is played by the user and the other by the engine, choosing which color they take.  
- **R-A2.** The user can choose the engine's difficulty before the game, on a scale that maps to the engine's strength controls (W-E2).  
- **R-A3.** The user can play *with* a time control (each side has a clock that counts down only on their turn) or *without* one.  
- **R-A4.** Only legal moves are ever committed to the game, for either the human or the engine.  
- **R-A5.** When the game reaches a terminal state (checkmate, stalemate, insufficient material, etc), the game ends, and the correct result (win/loss/draw and its cause) is shown.  
- **R-A6.** The user can start a game against the engine *from an arbitrary legal position* rather than the standard start.

2) ### Analysis board

- **R-B1.** The user can set up or arrive at any legal position and see the engine's evaluation of it, updated as the engine searches deeper.  
- **R-B2.** The user can see the engine's top *N* candidate lines (principal variations) for the current position, N being user-selectable.  
- **R-B3.** The user can build a **tree** of analysis: from any position they may add a move, creating a new node; multiple alternative moves from the same position coexist as sibling variations.  
- **R-B4.** The user can navigate the tree (to any node), delete a node together with its subtree, and promote/reorder variations.  
- **R-B5.** Every move the user adds to the analysis tree is legal in its parent position (follows from W-C1); the analysis tree never contains illegal positions.  
- **R-B6.** Engine analysis can be started and stopped by the user at will without corrupting the tree.

3) ###  Import/Export

- **R-C1.** The user can **export** the current position as FEN and the current game/tree as PGN (with variations preserved).  
- **R-C2.** The user can **import** a FEN to load a position, or a PGN to load a whole game or analysis, and continue from it.  
- **R-C3.** *Analyze an existing game:* given any game (imported as PGN, or the one just played), the user can walk its moves and invoke engine analysis at each position.  
- **R-C4.** *Play from a given position:* R-C2 (import FEN) \+ R-A6.  
- **R-C5.** Exporting then re-importing a position or game yields the same position/game.

4) ### Cross-cutting

- **R-D1.** The displayed board always reflects the currently viewed position; the user is never shown a state that does not correspond to a real node in the game/tree.  
- **R-D2.** Malformed user input (illegal move, bad FEN/PGN, unreadable file) is rejected with an explanation and leaves the existing state intact.

---

## 3\. Specification (S)

1) ### Rule enforcement

* **S-RULES1.** The machine keeps an internal representation of the current position, equivalent to what is described in W-C2, together with a legality check: a candidate move is committed to the game if and only if it is legal in that position (per W-C1).  
* **S-RULES2.** After each committed move, the machine determines whether the resulting position is checkmate or one of the draw conditions (stalemate, insufficient material, the fifty-move rule, or threefold repetition) and updates the game's status accordingly.  
* **S-RULES3.** The displayed board always shows the position of whichever node is currently being viewed, and is refreshed immediately whenever that view changes (serves R-D1).

2) ### The engine

* **S-ENG1.** The machine configures Stockfish using the specific option names and ranges given in W-E2 and W-E3, hardcoded rather than discovered at connection time.   
* **S-ENG2.** To set the engine's difficulty (R-A2), the machine configures whichever strength-limiting option the engine has advertised, translating the user's chosen difficulty into a valid value for that option.  
* **S-ENG3.** To obtain a move or an evaluation, the machine sends the position to be considered to the engine and asks it to search: bounded by a time or depth budget when playing a move, or left open-ended until the user stops it when analysing. As the engine reports progress, the displayed evaluation and recommended move update to match (serves R-B1).  
* **S-ENG4.** Before analysis begins, the machine tells the engine how many candidate lines to return, matching the number the user has chosen.  
* **S-ENG5.** Starting or stopping engine analysis never by itself changes the analysis tree; a line the engine suggests is only added to the tree when the user explicitly chooses to add it.  
* **S-ENG6.** Communication with the engine is time-bounded: if the engine does not respond within a reasonable time, or its process ends unexpectedly, the machine treats the engine as unavailable, tells the user so, and continues to support move entry, navigation, and import/export as normal.

3) ### Time control

* **S-CLOCK1.** In a timed game, the machine tracks each side's remaining time, counting down only the side to move's clock using the wall clock), and applies any agreed increment once a move is completed.  
* **S-CLOCK2.** If a side's clock reaches zero, the game ends immediately with a loss on time for that side.  
* **S-CLOCK3.** In an untimed game, no clock is tracked, and this behaviour never triggers.

4) ### Game analysis

* **S-TREE1.** The machine represents a game or analysis session as a tree of positions: every position but the first is reached from its parent by exactly one move, and a position may have more than one child when more than one move from it is under consideration. One path through the tree is distinguished as the mainline — at each branch point, the mainline follows whichever continuation is currently ranked first.  
* **S-TREE2.** Adding a move at a given position creates (or reuses, if it already exists) a child position reached by that move; a move is added only if it passes the legality check, so the tree never contains an illegal position (serves R-B3, R-B5).  
* **S-TREE3.** Deleting a position removes it and everything beneath it in the tree; if the deleted position was the one being viewed, the view falls back to its parent (serves R-B4).  
* **S-TREE4.** *Navigate:* the user can move the viewed position to any node in the tree, with the display updating accordingly (serves R-D1).  
* **S-TREE5.** *Upgrade/downgrade:* at a position with more than one continuation, the user can change the relative order of those continuations. If a continuation becomes first-ranked at that point, the mainline changes to follow it from there onward.  
* **S-TREE6.** *Promote a line to mainline:* given any position in the tree, the user can make the path from the root to that position the mainline in a single action. This ranks the continuation on that path first at every branch point along the way; the sibling order at branch points not on that path is unaffected

5) ### Import/export

* **S-IO1.** The machine can produce a FEN string for the position currently being viewed, and can accept a FEN string from the user, checking that it is well-formed and legal before loading it as the new current position).  
* **S-IO2.** The machine can produce a PGN representation of the whole tree, including every variation, not only the mainline.  
* **S-IO3.** The machine can read a PGN and reconstruct the tree it describes, including its variations..  
* **S-IO4.** Reading or writing a FEN or PGN can fail – for example, if the input is not well-formed, or a file cannot be reached. On failure, the machine reports the problem and leaves the existing state exactly as it was.

6) ###  User input handling

* **S-INPUT1.** A move the user indicates directly on the board (including a choice of promotion piece, where relevant) is treated as a candidate move and checked for legality before it is committed; an illegal candidate is rejected and shown as such, never applied.  
* **S-INPUT2.** In a game against the engine, the user's input is accepted only when it is their turn; on the engine's turn, the next move comes from the engine instead.