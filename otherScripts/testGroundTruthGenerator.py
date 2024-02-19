# -*- coding: utf-8 -*-
"""
Created on Mon Feb 19 22:42:11 2024

@author: Greg
"""

import chess
import numpy as np

Nparties = 100
NMovePerPartie = 10
fileToSave = "testFile.txt"

res = ""

for i in range(Nparties):
    game = []
    board = chess.Board()
    for j in range(50):
        allMoves = [m for m in board.legal_moves]
        game.append(board.fen() + "\n" + str(len(allMoves)) + "\n")
        if len(allMoves)>0:
            chosenMove = np.random.choice(allMoves)
            board.push(chosenMove)
        else:
            break
    exampleMoves = np.random.choice(game, size=NMovePerPartie, replace=False)
    for k in exampleMoves:
        res = res + k

f = open(fileToSave, mode = 'w')
f.write(res)
f.close()