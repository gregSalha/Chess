# -*- coding: utf-8 -*-
"""
Created on Mon Feb 19 22:42:11 2024

@author: Greg
"""

import chess
import numpy as np

def generateListOfFenPositions(Nparties, NMovePerPartie):
    res = []
    for i in range(Nparties):
        board = chess.Board()
        gameMove = []
        for j in range(50):
            allMoves = [m for m in board.legal_moves]
            if len(allMoves)>0:
                chosenMove = np.random.choice(allMoves)
                gameMove.append(board.fen(en_passant="fen"))
                board.push(chosenMove)
            else:
                break
        exampleMoves = list(np.random.choice(gameMove, size=min(NMovePerPartie, len(gameMove)),, replace=False))
        res = res + exampleMoves
    return res

def saveFENPositionList(file, Nparties, NmovePerPartie):
    res=""
    listFen = generateListOfFenPositions(Nparties, NmovePerPartie)
    for m in listFen:
        res = res + m + "\n"
    f = open(file, 'w', newline='')
    f.write(res)
    f.close()
    
def saveMoveCountFromFenList(file, Nparties, NmovePerPartie):
    res=""
    listFen = generateListOfFenPositions(Nparties, NmovePerPartie)
    for m in listFen:
        board = chess.Board(m)
        allMoves = [m for m in board.legal_moves]
        res = res + m + "\n" + str(len(allMoves)) + "\n"
    f = open(file, 'w', newline='')
    f.write(res)
    f.close()
    
def savePostionsAvaibleFromFen(file, Nparties, NmovePerPartie):
    res=""
    listFen = generateListOfFenPositions(Nparties, NmovePerPartie)
    for m in listFen:
        res = res + m + "\n"
        board = chess.Board(m)
        allMoves = [m for m in board.legal_moves]
        for possibleMove in allMoves:
            newBoard = chess.Board(m)
            newBoard.push(possibleMove)
            res = res + newBoard.fen(en_passant="fen") + "\n"
        res = res + "-#-\n"
    f = open(file, 'w', newline='')
    f.write(res)
    f.close()
    
if __name__=="__main__":
    saveFENPositionList("testFileFENPositions.txt", 100, 10)
    saveMoveCountFromFenList("testFilePositionCount.txt", 100, 10)
    savePostionsAvaibleFromFen("testFilePositionAvaible.txt", 100, 10)
