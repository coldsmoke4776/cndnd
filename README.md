

<h2>C&D&D - Version 1.0 </h2>

A single player, terminal-based Dungeons & Dragons-inspired RPG engine, written entirely in C

<h3>Overview</h3>

C&D&D is a narrative combat engine that is modelled closely to (but is a simplified version of) the D&D 5E ruleset. You can build a party, fight monsters, and the dice decide your fate, just like on the tabletop.

This is a personal learning project, written in C to explore concepts like:

<li>Pointers,</li>
<li>Memory Management (malloc, free),</li>
<li>Modular Project Design,</li>
<li>File I/O,</li>
<li>Game Logic</li>

<h3>Features (v1)</h3>

<li>Modular codebase (main.c, character.c, combat.c, bestiary.c, dicegoblin.c</li>
<li>Party system with ability scores, modifiers, AC, and HP</li>
<li>Combat loop with attack rolls, damage dice and initiative to sort turn order</li>
<li>Monster bestiary - I used actual stat blocks from https://www.dndbeyond.com/sources/dnd/br-2024 </li>
<li>Save/load party system in party.txt </li>
<li>Terminal-based play - no graphics card needed, I am fairly sure this would run on a potato with a battery taped to it.</li>


<h3>Installation</h3>

Clone the repo:
```
git clone https://github.com/coldsmoke4776/cndnd.git
cd cndnd
```

Build using make:
```
make
```

Run the game!
```
./cndnd
```

Clean the build files:
```
make clean
```


<h3>Example Gameplay</h3>


=== PARTY SUMMARY - Our intrepid adventurers ===

Tav - NE Fighter (HP: 40, AC: 15) STR: 18 (Mod: 4), DEX: 14 (Mod: 2), CON: 16 (Mod: 3) ...
=== An Encounter Begins! === An angry Goblin appears! (HP: 10, AC: 12, Att.Bon: 3, Dmg.Die: D6, Dmg.Bon: 0)

Tav hits the Goblin for 6 damage! (Enemy HP is now: 4)

Goblin misses their attack on Tav!

Goblin has been defeated!

<h3>Roadmap for future expansion</h3>

The idea is that future expansions will add items, levelling, spellcasting, ranged attacks and narrative arcs. Feel free to take this and run with it yourself!

