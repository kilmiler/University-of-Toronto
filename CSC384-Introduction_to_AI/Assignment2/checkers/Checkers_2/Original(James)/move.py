import typing

from piece import Position

class Move:
    def __init__(self, row: int, col: int):
        """
        Represents each move a player can make
        """
        self.row = row
        self.col = col

    def __str__(self):
        return '({}, {})'.format(self.row, self.col)

    def __repr__(self):
        return '({}, {})'.format(self.row, self.col)

    def __eq__(self, other):
        return self.row == other.row and self.col == other.col


class Action:
    def __init__(self, start_piece: Position, moves: typing.List[Move]):
        """
        Represents set of actions a player can make.
        Moves can either be a single move or multiple moves for multiple skips
        """
        self.start_piece = start_piece
        self.moves = moves

    def __repr__(self):
        return '<{} -> {}>'.format(self.start_piece, ' -> '.join(str(move) for move in self.moves))

    def __str__(self):
        return '<{} -> {}>'.format(self.start_piece, ' -> '.join(str(move) for move in self.moves))
