import typing
import copy

from move import Move
from piece import Position, PositionType


class State:
    def __init__(self, board, size=8):
        self.size = size
        self.board = copy.deepcopy(board)

    def get(self, row, col):
        """
        Gets position information for given row and col
        """
        piece = self.board[row][col]
        return Position(row, col, PositionType(piece))

    def set_state(self, moves: typing.List[Move], piece: Position):
        """
        Sets state based on list of moves made for the piece
        """
        prev_move = Move(piece.row, piece.col)
        for move in moves:
            self.board[prev_move.row][prev_move.col] = PositionType.EMPTY.value
            self.board[int((move.row + prev_move.row) / 2)][int((move.col + prev_move.col) / 2)] = PositionType.EMPTY.value
            self.board[move.row][move.col] = piece.type.value
            prev_move = move

    def __repr__(self):
        rows = [''.join(row) for row in self.board]
        return '{}'.format('\n'.join(rows))

    def __str__(self):
        rows = [''.join(row) for row in self.board]
        return '{}'.format('\n'.join(rows))
