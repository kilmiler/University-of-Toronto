def valid_moves(self, piece):
    # moves = {(possible_move_space1) : (gets_rid_of1), (possible_move_space2) : (gets_rid_of2)}
    moves = {}
    up = piece.row - 1
    down = piece.row + 1
    left = piece.col - 1
    right = piece.col + 1

    # print(piece.row)  # 0
    # print(piece.col)  # 3

    # print(moves)

    if piece.colour == 'r':
        is_left_up_in_board, is_left_up_empty = self.check_up_left(
            up, left)
        is_right_up_in_board, is_right_up_empty = self.check_up_right(
            up, right)

        print(is_left_up_empty, is_right_up_empty,
                is_left_up_in_board, is_right_up_in_board)

        if is_left_up_empty == True and is_left_up_in_board == True:
            print("up_left_EMPTY!")
            # Up Left Empty --> End Turn if taken
            moves[up, left] = [(up, left)]
            print(moves)
        if is_right_up_empty == True and is_right_up_in_board == True:
            print("up_right_EMPTY!")
            # Up Right Empty --> End Turn if taken
            moves[up, right] = [(up, right)]
            print(moves)

        while (is_left_up_empty == False and is_left_up_in_board == True) or (is_right_up_empty == False and is_right_up_in_board == True):
            if is_left_up_empty == False and is_left_up_in_board == True and self.board[up-1][left-1].colour != 'b' and self.board[up-1][left-1].colour != 'B':
                print("up_left_BLACK!")
                # Up Left Black --> Must Capture --> Check Valid Moves Again
                up_temp = up - 1  #
                left_temp = left - 1  #

                if (up_temp+2, left_temp+2) in moves:
                    print("UPDATE")
                    moves[up_temp, left_temp] = moves[up_temp+2, left_temp+2]
                    del moves[up_temp+2, left_temp+2]
                    moves[up_temp-1, left_temp -
                            1].append((up_temp+1, left_temp+1))
                else:
                    print("NEW")
                    moves[up_temp, left_temp] = [(up_temp+1, left_temp+1)]

                up -= 2
                left -= 2
                right -= 2

                is_left_up_in_board, is_left_up_empty = self.check_up_left(
                    up, left)
                is_right_up_in_board, is_right_up_empty = self.check_up_right(
                    up, right)

                print(is_left_up_empty, is_right_up_empty,
                        is_left_up_in_board, is_right_up_in_board)
                print(moves)

            if is_right_up_empty == False and is_right_up_in_board == True and self.board[up-1][right+1].colour != 'b' and self.board[up-1][right+1].colour != 'B':
                print("up_right_BLACK!")
                # Up Right Black --> Must Capture --> Check Valid Moves Again
                up_temp = up - 1
                right_temp = right + 1

                if (up_temp+2, right_temp-2) in moves:
                    print("UPDATE")
                    moves[up_temp, right_temp] = moves[up_temp+2, right_temp-2]
                    del moves[up_temp+2, right_temp-2]
                    moves[up_temp, right_temp].append(
                        (up_temp+1, right_temp-1))
                else:
                    print("NEW")
                    moves[up_temp, right_temp] = [(
                        up_temp+1, right_temp-1)]

                up -= 2
                left += 2
                right += 2

                is_left_up_in_board, is_left_up_empty = self.check_up_left(
                    up, left)
                is_right_up_in_board, is_right_up_empty = self.check_up_right(
                    up, right)

                print(is_left_up_empty, is_right_up_empty,
                        is_left_up_in_board, is_right_up_in_board)
                print(moves)

    if piece.colour == 'R':
        is_left_up_in_board, is_left_up_empty = self.check_up_left(
            up, left)
        is_right_up_in_board, is_right_up_empty = self.check_up_right(
            up, right)
        is_left_down_in_board, is_left_down_empty = self.check_down_left(
            down, left)
        is_right_down_in_board, is_right_down_empty = self.check_down_right(
            down, right)

        print(is_left_up_empty, is_right_up_empty,
                is_left_up_in_board, is_right_up_in_board)
        print(is_left_down_empty, is_right_down_empty,
                is_left_down_in_board, is_right_down_in_board)

        if is_left_up_empty == True and is_left_up_in_board == True:
            print("up_left_EMPTY!")
            # Up Left Empty --> End Turn if taken
            moves[up, left] = [(up, left)]
            print(moves)
        if is_right_up_empty == True and is_right_up_in_board == True:
            print("up_right_EMPTY!")
            # Up Right Empty --> End Turn if taken
            moves[up, right] = [(up, right)]
            print(moves)
        if is_left_down_empty == True and is_left_down_in_board == True:
            print("down_left_EMPTY!")
            # Down Left Empty --> End Turn if taken
            moves[down, left] = [(down, left)]
            print(moves)
        if is_right_down_empty == True and is_right_down_in_board == True:
            print("down_right_EMPTY!")
            # Down Right Empty --> End Turn if taken
            moves[down, right] = [(down, right)]
            print(moves)

        while (is_left_up_empty == False and is_left_up_in_board == True) or (is_right_up_empty == False and is_right_up_in_board == True) or (is_left_down_empty == False and is_left_down_in_board == True) or (is_right_down_empty == False and is_right_down_in_board == True):
            if is_left_up_empty == False and is_left_up_in_board == True and self.board[up-1][left-1].colour != 'b' and self.board[up-1][left-1].colour != 'B':
                print("up_left_BLACK!")
                # Up Left Black --> Must Capture --> Check Valid Moves Again
                up_temp = up - 1  #
                left_temp = left - 1  #

                if (up_temp+2, left_temp+2) in moves:
                    print("UPDATE")
                    moves[up_temp, left_temp] = moves[up_temp+2, left_temp+2]
                    del moves[up_temp+2, left_temp+2]
                    moves[up_temp, left_temp].append(
                        (up_temp+1, left_temp+1))
                else:
                    print("NEW")
                    moves[up_temp, left_temp] = [(up_temp+1, left_temp+1)]

                up -= 2
                down -= 2
                left -= 2
                right -= 2

                is_left_up_in_board, is_left_up_empty = self.check_up_left(
                    up, left)
                is_right_up_in_board, is_right_up_empty = self.check_up_right(
                    up, right)
                is_left_down_in_board, is_left_down_empty = self.check_down_left(
                    down, left)
                is_right_down_in_board = False

                print(moves)

            if is_right_up_empty == False and is_right_up_in_board == True and self.board[up-1][right+1].colour != 'b' and self.board[up-1][right+1].colour != 'B':
                print("up_right_BLACK!")
                # Up Right Black --> Must Capture --> Check Valid Moves Again
                up_temp = up - 1
                right_temp = right + 1

                if (up_temp+2, right_temp-2) in moves:
                    print("UPDATE")
                    moves[up_temp, right_temp] = moves[up_temp+2, right_temp-2]
                    del moves[up_temp+2, right_temp-2]
                    moves[up_temp, right_temp].append(
                        (up_temp+1, right_temp-1))
                else:
                    print("NEW")
                    moves[up_temp, right_temp] = [(
                        up_temp+1, right_temp-1)]

                up -= 2
                down -= 2
                left += 2
                right += 2

                is_left_up_in_board, is_left_up_empty = self.check_up_left(
                    up, left)
                is_right_up_in_board, is_right_up_empty = self.check_up_right(
                    up, right)
                is_left_down_in_board = False
                is_right_down_in_board, is_right_down_empty = self.check_down_right(
                    down, right)

                print(moves)

            if is_left_down_empty == False and is_left_down_in_board == True and self.board[down+1][left-1].colour != 'b' and self.board[down+1][left-1].colour != 'B':
                print("down_left_BLACK!")
                # Down Left Black --> Must Capture --> Check Valid Moves Again
                down_temp = down + 1  #
                left_temp = left - 1  #

                if (down_temp-2, left_temp+2) in moves:
                    print("UPDATE")
                    moves[down_temp, left_temp] = moves[down_temp-2, left_temp+2]
                    del moves[down_temp-2, left_temp+2]
                    moves[down_temp, left_temp].append(
                        (down_temp-1, left_temp+1))
                else:
                    print("NEW")
                    moves[down_temp, left_temp] = [
                        (down_temp-1, left_temp+1)]

                up += 2
                down += 2
                left -= 2
                right -= 2

                is_left_up_in_board, is_left_up_empty = self.check_up_left(
                    up, left)
                is_right_up_in_board = False
                is_left_down_in_board, is_left_down_empty = self.check_down_left(
                    down, left)
                is_right_down_in_board, is_right_down_empty = self.check_down_right(
                    down, right)

                print(moves)

            if is_right_down_empty == False and is_right_down_in_board == True and self.board[down+1][right+1].colour != 'b' and self.board[down+1][right+1].colour != 'B':
                print("down_right_BLACK!")
                # Down Left Black --> Must Capture --> Check Valid Moves Again
                down_temp = down + 1  #
                right_temp = right + 1  #

                if (down_temp-2, right_temp-2) in moves:
                    print("UPDATE")
                    moves[down_temp, right_temp] = moves[down_temp -
                                                            2, right_temp-2]
                    del moves[down_temp-2, right_temp-2]
                    moves[down_temp, right_temp].append(
                        (down_temp-1, right_temp-1))
                else:
                    print("NEW")
                    moves[down_temp, right_temp] = [
                        (down_temp-1, right_temp-1)]

                up += 2
                down += 2
                left += 2
                right += 2

                is_left_up_in_board = False
                is_right_up_in_board, is_right_up_empty = self.check_up_right(
                    up, right)
                is_left_down_in_board, is_left_down_empty = self.check_down_left(
                    down, left)
                is_right_down_in_board, is_right_down_empty = self.check_down_right(
                    down, right)

                print(moves)

def check_up_left(self, up, left):
    is_left_up_in_board = True
    is_left_up_empty = True

    if left < 0 or up < 0:
        is_left_up_in_board = False
        is_left_up_empty = False
    elif self.board[up][left].colour == 'b' or self.board[up][left].colour == 'B':
        is_left_up_empty = False

    return is_left_up_in_board, is_left_up_empty

def check_up_right(self, up, right):
    is_right_up_in_board = True
    is_right_up_empty = True

    if right > 7 or up < 0:
        is_right_up_in_board = False
        is_right_up_empty = False
    elif self.board[up][right].colour == 'b' or self.board[up][right].colour == 'B':
        is_right_up_empty = False

    return is_right_up_in_board, is_right_up_empty

def check_down_left(self, down, left):
    is_left_down_in_board = True
    is_left_down_empty = True

    if left < 0 or down < 0:
        is_left_down_in_board = False
        is_left_down_empty = False
    elif self.board[down][left].colour == 'b' or self.board[down][left].colour == 'B':
        is_left_down_empty = False

    return is_left_down_in_board, is_left_down_empty

def check_down_right(self, down, right):
    is_right_down_in_board = True
    is_right_down_empty = True

    if right > 7 or down < 0:
        is_right_down_in_board = False
        is_right_down_empty = False
    elif self.board[down][right].colour == 'b' or self.board[down][right].colour == 'B':
        is_right_down_empty = False

    return is_right_down_in_board, is_right_down_empty
