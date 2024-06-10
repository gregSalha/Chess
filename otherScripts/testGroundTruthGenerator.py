# -*- coding: utf-8 -*-
"""
Created on Mon Feb 19 22:42:11 2024

@author: Greg
"""

import chess
import numpy as np
import json

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
        exampleMoves = list(np.random.choice(gameMove, size=min(NMovePerPartie, len(gameMove)), replace=False))
        res = res + exampleMoves
    return res

def saveFENPositionList(file, Nparties, NmovePerPartie):
    res=[]
    listFen = generateListOfFenPositions(Nparties, NmovePerPartie)
    for m in listFen:
        res.append(m)
    f = open(file, 'w', newline='')
    f.write(json.dumps(res, sort_keys=True, indent=4))
    f.close()
    
def saveMoveCountFromFenList(file, Nparties, NmovePerPartie):
    res = []
    listFen = generateListOfFenPositions(Nparties, NmovePerPartie)
    for m in listFen:
        newValue = {}
        board = chess.Board(m)
        allMoves = [m for m in board.legal_moves]
        newValue["fenPosition"] = m
        newValue["count"] = len(allMoves)
        res.append(newValue)

    f = open(file, 'w', newline='')
    f.write(json.dumps(res, sort_keys=True, indent=4))
    f.close()
    
def savePositionsAvaibleFromFen(file, Nparties, NmovePerPartie):
    res = []
    listFen = generateListOfFenPositions(Nparties, NmovePerPartie)
    for m in listFen:
        newValue = {}
        newValue["fenStartingPosition"] = m
        board = chess.Board(m)
        allMoves = [m for m in board.legal_moves]
        newValue["avaiblePositions"] = []
        for possibleMove in allMoves:
            newBoard = chess.Board(m)
            newBoard.push(possibleMove)
            newValue["avaiblePositions"].append(newBoard.fen(en_passant="fen"))
        res.append(newValue)
    f = open(file, 'w', newline='')
    f.write(json.dumps(res, sort_keys=True, indent=4))
    f.close()
    
if __name__=="__main__":
    saveFENPositionList("testFileFENPositions.json", 100, 10)
    saveMoveCountFromFenList("testFilePositionCount.json", 100, 10)
    savePositionsAvaibleFromFen("testFilePositionAvaible.json", 100, 10)
