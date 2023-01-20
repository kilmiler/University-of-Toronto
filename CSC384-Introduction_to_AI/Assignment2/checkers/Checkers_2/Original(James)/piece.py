import enum


class PositionType(enum.Enum):
    RED = 'r'
    RED_KING = 'R'
    BLACK = 'b'
    BLACK_KING = 'B'
    EMPTY = '.'


class Color:
    RED = 'red'
    BLACK = 'black'


POSITION_TYPE_TO_COLOR = {
    PositionType.RED: Color.RED,
    PositionType.RED_KING: Color.RED,
    PositionType.BLACK: Color.BLACK,
    PositionType.BLACK_KING: Color.BLACK,
    PositionType.EMPTY: None,
}


class Position:
    def __init__(self, row: int, col: int, position_type: PositionType):
        self.row = row
        self.col = col
        self.type = position_type
        self.color = POSITION_TYPE_TO_COLOR[position_type]
        self.is_king = position_type in {PositionType.RED_KING, PositionType.BLACK_KING}

    def __str__(self):
        return '{} ({}, {})'.format(self.type.value, self.row, self.col)
