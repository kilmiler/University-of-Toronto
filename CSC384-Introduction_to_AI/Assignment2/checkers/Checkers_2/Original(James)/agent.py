import time
from tkinter import CURRENT
import typing

from state import State
from move import Move, Action
from piece import Position, PositionType, Color


TIMEOVER_CUTOFF = float('-inf')  # cutoff value for timeover
NEGATIVE_INF = float('-inf')
POSITIVE_INF = float('inf')

class Direction:
    UP = -1
    DOWN = 1


class Agent:
    def __init__(self, max_time_s=300, player_color=Color.RED):
        self.max_time_ms = max_time_s * 1000
        self.player_color = player_color
        self.opponent_color = Color.BLACK if player_color == Color.RED else Color.RED

    def move(self, state: State):
        # TODO: implement this
        pass

    def get_actions(self, state, current_color):
        """
        Returns all available actions for this agent
        """
        actions: typing.List[Move] = []

        row_direction = Direction.UP if current_color == Color.RED else Direction.DOWN

        for i in range(state.size):
            for j in range(state.size):
                piece = state.get(i, j)

                if piece.type == PositionType.EMPTY:
                    continue

                row_directions = [Direction.UP, Direction.DOWN] if piece.is_king else [row_direction]

                if piece.color == current_color:
                    actions.extend(self.get_valid_actions(state, piece, row_directions))
                    actions.extend(self.get_valid_skip_actions(state, piece, row_directions))

        return actions

    def get_valid_actions(self, state: State, piece: Position, row_directions: typing.List[int]):
        """
        Returns all valid actions that a player can make, excluding skips
        """
        valid_actions = []

        for direction in row_directions:
            new_row = piece.row + direction

            if new_row < 0 or new_row >= state.size:
                continue

            for col_direction in [-1, 1]:
                new_col = piece.col + col_direction
                if new_col < 0 or new_col >= state.size:
                    continue
                moved_position = state.get(new_row, new_col)
                if moved_position.type == PositionType.EMPTY:
                    valid_actions.append(
                        Action(
                            start_piece=piece,
                            moves=[Move(new_row, new_col)],
                        )
                    )

        return valid_actions

    def get_valid_skip_actions(self, state: State, piece: Position, row_directions: typing.List[int]):
        """
        Returns valid skip actions a player can make
        """
        skip_move_list = []
        self.get_valid_skip_moves(state, piece, row_directions, skip_move_list, [])
        skip_actions = [
            Action(start_piece=piece, moves=skip_moves)
            for skip_moves in skip_move_list
        ]
        return skip_actions

    def get_valid_skip_moves(
            self,
            state: State,
            piece: Position,
            row_directions: typing.List[int],
            skip_move_list: typing.List[typing.List[Move]],
            prev_moves: typing.List[Move],
        ):
        """
        Recursively get valid skip moves
        """
        skip_moves = []

        for direction in row_directions:
            new_row = piece.row + (direction * 2)
            for col_direction in [-1, 1]:
                new_col = piece.col + (col_direction * 2)
                new_move = Move(new_row, new_col)
                if new_move in prev_moves:
                    continue

                if self.is_valid_skip_move(state, new_row, new_col, piece):
                    skip_moves.append(new_move)

        if not skip_moves:
            return True

        for move in skip_moves:
            next_moves = prev_moves + [move]
            is_terminal = self.get_valid_skip_moves(
                state,
                Position(move.row, move.col, piece.type),
                row_directions,
                skip_move_list,
                next_moves,
            )

            if is_terminal:
                skip_move_list.append(next_moves)

        return False

    def is_valid_skip_move(self, state: State, row: int, col: int, piece: Position):
        if row < 0 or row >= state.size:
            return False
        if col < 0 or col >= state.size:
            return False
        new_piece = state.get(row, col)
        if new_piece.type != PositionType.EMPTY:
            return False
        
        skipped_piece = state.get(int((piece.row + row) / 2), int((piece.col + col) / 2))
        return skipped_piece.type != PositionType.EMPTY and skipped_piece.color != piece.color
