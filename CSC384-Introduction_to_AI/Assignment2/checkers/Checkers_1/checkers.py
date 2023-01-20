# from ctypes import sizeof
from ast import AsyncFunctionDef
from copy import copy, deepcopy
from queue import Empty
import numpy as np
import sys



inputfile = sys.argv[1]
outputfile = sys.argv[2]


# f = open('/Users/hee/Documents/UT/Y4/Fall(4-1)/384/Assignment2/checkers_validate/input0.txt', 'r')
f = open(inputfile, 'r')
f.close
input_content = f.readlines()


def main():
    initial_board = Board()
    initial_board.create_board_from_input(input_content)

    print("INITIAL BOARD:")
    for row in range(8):
        print(initial_board.board[row])

    depth = 8
    #Using Minimax
    #value, best_board = initial_board.minimax_max(initial_board.board, depth)
    #Using Alpha-Beta Pruning
    value, best_board = initial_board.alphabeta_max(initial_board.board, depth, float('-inf'), float('inf'))

    print("BEST BOARD:")
    for row in range(8):
        print(best_board[row])

    # Save to File "output#.txt"
    with open(outputfile, 'w') as f:
        for row in best_board:
            for piece in row:
                if(piece.colour == '0'):
                    f.write(".")
                if(piece.colour == 'r'):
                    f.write("r")
                if(piece.colour == 'R'):
                    f.write("R")
                if(piece.colour == 'b'):
                    f.write("b")
                if(piece.colour == 'B'):
                    f.write("B")
            f.write("\n")



class Board:
    def __init__(self):
        self.board = []
        self.num_red_man = self.num_black_man = 0
        self.num_red_king = self.num_black_king = 0

    #############
    ## MINIMAX ##
    #############

    def minimax_max(self, state, depth):
        #Check if end of depth, or winner is evaluated
        is_winner = self.is_winner(state)
        if depth == 0 or is_winner != None:
            return self.evaluate_utility(state), state #

        #set value to -infinity for Max
        evalMax = float('-inf') #
        best_move = None #

        for move in self.get_possible_states_red(state):
            eval = self.minimax_min(move, depth-1)[0]

            if evalMax < eval:
                evalMax = eval
                best_move = move

        return evalMax, best_move

    def minimax_min(self, state, depth):
        #Check if end of depth, or winner is evaluated
        is_winner = self.is_winner(state)
        if depth == 0 or is_winner != None:
            return self.evaluate_utility(state), state

        #set value to +infinity for Min
        evalMin = float('inf')
        best_move = None

        for move in self.get_possible_states_black(state):
            eval = self.minimax_max(move, depth-1)[0]
            
            if evalMin > eval:
                evalMin = eval
                best_move = move

            return evalMin, best_move

    ##################################
    ## ALPHA-BETA PRUNING + MINIMAX ##
    ##################################

    def alphabeta_max(self, state, depth, alpha, beta):
        #Check if end of depth, or winner is evaluated
        is_winner = self.is_winner(state)
        if depth == 0 or is_winner != None:
            return self.evaluate_utility(state), state

        #set value to -infinity for Max
        evalMax = float('-inf')
        best_move = None

        for move in self.get_possible_states_red(state):
            eval = self.alphabeta_min(move, depth-1, alpha, beta)[0]
            #print("MAXeval", eval)

            if evalMax < eval:
                evalMax = eval
                best_move = move
            
            if evalMax >= beta:
                return evalMax, best_move 

            alpha = max(alpha, evalMax)

        return evalMax, best_move

    def alphabeta_min(self, state, depth, alpha, beta):
        #Check if end of depth, or winner is evaluated
        is_winner = self.is_winner(state)
        if depth == 0 or is_winner != None:
            return self.evaluate_utility(state), state

        #set value to +infinity for Min
        evalMin = float('inf')
        best_move = None

        for move in self.get_possible_states_black(state):
            eval = self.alphabeta_max(move, depth-1, alpha, beta)[0]
            #print("MINeval", eval)
            
            if evalMin > eval:
                evalMin = eval
                best_move = move
            
            if evalMin <= alpha:
                return evalMin, best_move

            beta = min(beta, evalMin)

            return evalMin, best_move

    ##################################
    ## HEURISTIC FUNCTION (UTILITY) ##
    ##################################

    def evaluate_utility(self, board):
        self.num_red_man = 0
        self.num_red_king = 0
        self.num_black_man = 0
        self.num_black_king = 0
        points_wall_red = 0
        points_wall_black = 0
        points_center_red = 0
        points_center_black = 0

        for row in board:
            for piece in row:
                up = piece.row - 1
                down = piece.row + 1
                left = piece.col - 1
                right = piece.col + 1

                if piece.colour == 'r':
                    self.num_red_man += 1
                if piece.colour == 'R':
                    self.num_red_king += 1
                if piece.colour == 'b':
                    self.num_black_man += 1
                if piece.colour == 'B':
                    self.num_black_king += 1
                
                if (piece.colour == 'r' or piece.colour == 'R'):
                    #If Red sticked to wall
                    if (piece.col == 0 or piece.col == 7):
                        points_wall_red += 0.5
                    #If Red takes center
                    if ((piece.col >= 2 and piece.col <= 5) and (piece.row >= 2 and piece.row <= 5)):
                        # without Black's threat
                        if (board[up][left] != 'b') or (board[up][left] == 'b' and board[down][right] != '0'):
                            if (board[up][left] != 'B') or (board[up][left] == 'B' and board[down][right] != '0'):
                                if (board[up][right] != 'b') or (board[up][right] == 'b' and board[down][left] != '0'):
                                    if (board[up][right] != 'B') or (board[up][right] == 'B' and board[down][left] != '0'):
                                            if (board[down][left] != 'B') or (board[down][left] == 'B' and board[up][right] != '0'):
                                                if (board[down][right] != 'B') or (board[down][right] == 'B' and board[up][left] != '0'):
                                                    if(piece.colour == 'r'):
                                                        points_center_red += 0.5
                                                    if(piece.colour == 'R'):
                                                        points_center_red += 1
                                                    
                if (piece.colour == 'b' or piece.colour == 'B'):
                    #If Black sticked to wall
                    if (piece.col == 0 or piece.col == 7):
                        points_wall_black += 0.5
                    #If Black takes center
                    if ((piece.col >= 2 and piece.col <= 5) and (piece.row >= 2 and piece.row <= 5)):
                        # without Reds's threat
                        if (board[down][left] != 'r') or (board[down][left] == 'r' and board[up][right] != '0'):
                            if (board[down][left] != 'R') or (board[down][left] == 'R' and board[up][right] != '0'):
                                if (board[down][right] != 'r') or (board[down][right] == 'r' and board[up][left] != '0'):
                                    if (board[down][right] != 'R') or (board[down][right] == 'R' and board[up][left] != '0'):
                                            if (board[up][left] != 'R') or (board[up][left] == 'R' and board[down][right] != '0'):
                                                if (board[up][right] != 'R') or (board[up][right] == 'R' and board[down][left] != '0'):
                                                    if(piece.colour == 'b'):
                                                        points_center_black += 0.5
                                                    if(piece.colour == 'B'):
                                                        points_center_black += 1

        points_num_red = (self.num_red_man + (self.num_red_king * 2))
        points_num_black = (self.num_black_man + (self.num_black_king * 2))
        
        points_num = (points_num_red - points_num_black)
        points_wall = (points_wall_red - points_wall_black)
        points_center = (points_center_red - points_center_black)

        points_total = points_num + points_wall + points_center

        utility = points_total
        return utility

    #####################
    ## BOARD FUNCTIONS ##
    #####################

    def create_board_from_input(self, input):
        for row in range(8):
            self.board.append([])
            for col in range(8):
                if input[row][col] == 'r':
                    self.board[row].append(Piece(row, col, 'r'))
                    self.num_red_man += 1
                if input[row][col] == 'R':
                    self.board[row].append(Piece(row, col, 'R'))
                    self.num_red_king += 1
                if input[row][col] == 'b':
                    self.board[row].append(Piece(row, col, 'b'))
                    self.num_black_man += 1
                if input[row][col] == 'B':
                    self.board[row].append(Piece(row, col, 'B'))
                    self.num_black_king += 1
                if input[row][col] == '.':
                    self.board[row].append(Piece(row, col, '0'))

    def move_board(self, piece, new_row, new_col):
        temp = self.board[piece.row][piece.col]
        self.board[piece.row][piece.col] = self.board[new_row][new_col]
        self.board[new_row][new_col] = temp

        piece.move_piece(new_row, new_col)

        if piece.colour == 'r' and piece.row == 0:
            piece.colour = 'R'
            self.num_red_king += 1
            self.num_red_man -= 1
        
        if piece.colour == 'b' and piece.row == 7:
            piece.colour = 'B'
            self.num_black_king += 1
            self.num_black_man -= 1

    def change_piece_to_empty(self, piece):
        self.board[piece.row][piece.col].colour = '0'

    def return_piece(self, row, col):
        return self.board[row][col]

    def get_all_pieces(self, colour):
        pieces = []
        for row in self.board:
            for piece in row:
                if piece.colour != '0' and piece.colour == colour:
                    pieces.append(piece)
        
        return pieces

    def is_winner(self, board):
        red_moves = self.get_possible_states_red(board)
        black_moves = self.get_possible_states_black(board)

        if (self.num_black_man + self.num_black_king <= 0) or len(black_moves) == 0:
            return 'RED'
        elif (self.num_red_man + self.num_red_king <= 0) or len(red_moves) == 0:
            return 'BLACK'
        else:
            return None

    
    def refresh_kings(self, board):
        count = 0
        for row in board.board:
            for piece in row:
                if piece.colour == 'b' and count == 7:
                    piece.colour = 'B'
                if piece.colour == 'r' and count == 0:
                    piece.colour = 'R'
            count += 1

    
    def stimulate_move(self, piece, init_row, init_col, board, removed, skipped):
        #print(piece.row, piece.col) # HERE IT SHOULD MOVE TO

        if skipped == False:
            #print("NOT SKIPPED!")
            board.move_board(piece, init_row, init_col)
        if skipped == True:
            #print("SKIPPED!")
            #(Where it Moved To, Where it Came From)
            board.move_board(piece, init_row, init_col)
            for piece in removed:
                delete_piece = board.return_piece(piece[0], piece[1])
                board.change_piece_to_empty(delete_piece)

        board.refresh_kings(board)
        #print("new Board:", board.board)
        return board

    def get_possible_states_red(self, board):
        moves = []
        skipped = False

        for piece in self.get_all_pieces('r'):
            temp_board = Board()
            temp_board_data = deepcopy(board)
            temp_board.board = temp_board_data
            init_row = piece.row
            init_col = piece.col
            valid_moves, skipped = temp_board.valid_moves_for_one_red(piece)

            for moved, removed in valid_moves.items():
                #print("PIECE:", piece.colour, "moved to:", moved)
                #print("removed:", removed)
                piece.row = moved[0]
                piece.col = moved[1]
                temp_board_2 = Board()
                temp_board_data_2 = deepcopy(temp_board.board)
                temp_board_2.board = temp_board_data_2
                new_board = self.stimulate_move(piece, init_row, init_col, temp_board_2, removed, skipped)
                moves.append(new_board.board)

        for piece in self.get_all_pieces('R'):
            temp_board = Board()
            temp_board_data = deepcopy(board)
            temp_board.board = temp_board_data
            init_row = piece.row
            init_col = piece.col
            valid_moves, skipped = temp_board.valid_moves_for_one_red(piece)

            for moved, removed in valid_moves.items():
                #print("PIECE:", piece.colour, "moved to:", moved)
                #print("removed:", removed)
                piece.row = moved[0]
                piece.col = moved[1]
                temp_board_2 = Board()
                temp_board_data_2 = deepcopy(temp_board.board)
                temp_board_2.board = temp_board_data_2
                new_board = self.stimulate_move(piece, init_row, init_col, temp_board_2, removed, skipped)
                moves.append(new_board.board)

        return moves

    def valid_moves_for_one_red(self, piece):
        moves = {}
        up = piece.row - 1
        down = piece.row + 1
        left = piece.col - 1
        right = piece.col + 1

        mandatory_capture = False
        skipped = False

        keys = list(moves)

        mandatory_capture = self.traverse_red(moves, piece, keys, up, down, left, right, mandatory_capture, skipped)
        #print(mandatory_capture, skipped)
        
        if mandatory_capture == True:
            skipped = True
            keys = list(moves)
            while(keys != []):
                for key in keys:
                    #print("key:", key)
                    piece.row = key[0]
                    piece.col = key[1]
                    up = piece.row - 1
                    down = piece.row + 1
                    left = piece.col - 1
                    right = piece.col + 1
                    mandatory_capture = self.traverse_red(moves, piece, keys, up, down, left, right, mandatory_capture, skipped)
                    #print(mandatory_capture, skipped)
                    #print("keys:", keys)

        #print("moves:", moves)
        return moves, skipped

    def traverse_red(self, moves, piece, keys, up, down, left, right, mandatory_capture, skipped):
        is_left_up_empty, is_left_up_skip = self.check_up_left(up, left, 'RED')
        is_right_up_empty, is_right_up_skip = self.check_up_right(up, right, 'RED')
        is_left_down_empty, is_left_down_skip = self.check_down_left(down, left, 'RED')
        is_right_down_empty, is_right_down_skip = self.check_down_right(down, right, 'RED')
        mandatory_capture = mandatory_capture
        skipped = skipped
        moved = False

        if skipped == True:
            for i in range(len(moves[piece.row, piece.col])):
                if (piece.row-1, piece.col-1) == moves[piece.row, piece.col][i]:
                    is_left_up_skip = False
                    #print("YAY1")
                if (piece.row-1, piece.col+1) == moves[piece.row, piece.col][i]:
                    is_right_up_skip = False
                    #print("YAY2")
                if (piece.row+1, piece.col-1) == moves[piece.row, piece.col][i]:
                    is_left_down_skip = False
                    #print("YAY3")
                if (piece.row+1, piece.col+1) == moves[piece.row, piece.col][i]:
                    is_right_down_skip = False
                    #print("YAY4")

            copy_values = moves[piece.row, piece.col]
            #print("copy_values:", copy_values)
            #print(len(copy_values))

            keys.remove(tuple((piece.row, piece.col)))


        if is_left_up_empty == False and is_left_up_skip == True:
            #print("UP LEFT BLACK!")
            if skipped == True:
                moves[up-1, left-1] = [(up, left)]
                for i in range(len(copy_values)):
                    moves[up-1, left-1].append(tuple(copy_values[i]))
            else:
                moves[up-1, left-1] = [(up, left)]
            mandatory_capture = True
            moved = True
            keys.append(tuple((up-1, left-1)))
            #print(moves)

        if is_right_up_empty== False and is_right_up_skip == True:
            #print("UP RIGHT BLACK!")
            if skipped == True:
                moves[up-1, right+1] = [(up, right)]
                for i in range(len(copy_values)):
                    moves[up-1, right+1].append(tuple(copy_values[i]))
            else:
                moves[up-1, right+1] = [(up, right)]
            mandatory_capture = True
            moved = True
            keys.append(tuple((up-1, right+1)))
            #print(moves)

        if piece.colour == 'R':
            if is_left_down_empty == False and is_left_down_skip == True:
                #print("DOWN LEFT BLACK!")
                if skipped == True:
                    moves[down+1, left-1] = [(down, left)]
                    for i in range(len(copy_values)):
                        moves[down+1, left-1].append(tuple(copy_values[i]))
                else:
                    moves[down+1, left-1] = [(down, left)]
                mandatory_capture = True
                moved = True
                keys.append(tuple((down+1, left-1)))
                #print(moves)

            if is_right_down_empty == False and is_right_down_skip == True:
                #print("DOWN RIGHT BLACK!")
                if skipped == True:
                    moves[down+1, right+1] = [(down, right)]
                    for i in range(len(copy_values)):
                        moves[down+1, right+1].append(tuple(copy_values[i]))
                else:
                    moves[down+1, right+1] = [(down, right)]
                mandatory_capture = True
                moved = True
                keys.append(tuple((down+1, right+1)))
                #print(moves)

        if is_left_up_empty == True and is_left_up_skip == False and mandatory_capture == False:
            #print("UP LEFT EMPTY!")
            moves[up, left] = [(up, left)]

        if is_right_up_empty == True and is_right_up_skip == False and mandatory_capture == False:
            #print("UP RIGHT EMPTY!")
            moves[up, right] = [(up, right)]

        if piece.colour == 'R':
            if is_left_down_empty == True and is_left_down_skip == False and mandatory_capture == False:
                #print("DOWN LEFT EMPTY!")
                moves[down, left] = [(down, left)]

            if is_right_down_empty == True and is_right_down_skip == False and mandatory_capture == False:
                #print("DOWN RIGHT EMPTY!")
                moves[down, right] = [(down, right)]

        if skipped == True and moved == True:
            del moves[piece.row, piece.col]

        #print("LOOP DONE")
        #print(moves)

        return mandatory_capture

    def get_possible_states_black(self, board):
        moves = []
        skipped = False

        for piece in self.get_all_pieces('b'):
            temp_board = Board()
            temp_board_data = deepcopy(board)
            temp_board.board = temp_board_data
            init_row = piece.row
            init_col = piece.col
            valid_moves, skipped = temp_board.valid_moves_for_one_black(piece)

            for moved, removed in valid_moves.items():
                #print("PIECE:", piece.colour, "moved to:", moved)
                #print("removed:", removed)
                piece.row = moved[0]
                piece.col = moved[1]
                temp_board_2 = Board()
                temp_board_data_2 = deepcopy(temp_board.board)
                temp_board_2.board = temp_board_data_2
                new_board = self.stimulate_move(piece, init_row, init_col, temp_board_2, removed, skipped)
                moves.append(new_board.board)

        for piece in self.get_all_pieces('B'):
            temp_board = Board()
            temp_board_data = deepcopy(board)
            temp_board.board = temp_board_data
            init_row = piece.row
            init_col = piece.col
            valid_moves, skipped = temp_board.valid_moves_for_one_black(piece)

            for moved, removed in valid_moves.items():
                #print("PIECE:", piece.colour, "moved to:", moved)
                #print("removed:", removed)
                piece.row = moved[0]
                piece.col = moved[1]
                temp_board_2 = Board()
                temp_board_data_2 = deepcopy(temp_board.board)
                temp_board_2.board = temp_board_data_2
                new_board = self.stimulate_move(piece, init_row, init_col, temp_board_2, removed, skipped)
                moves.append(new_board.board)

        return moves

    def valid_moves_for_one_black(self, piece):
        moves = {}
        up = piece.row - 1
        down = piece.row + 1
        left = piece.col - 1
        right = piece.col + 1

        mandatory_capture = False
        skipped = False

        keys = list(moves)

        mandatory_capture = self.traverse_black(moves, piece, keys, up, down, left, right, mandatory_capture, skipped)
        #print(mandatory_capture, skipped)
        
        if mandatory_capture == True:
            skipped = True
            keys = list(moves)
            while(keys != []):
                for key in keys:
                    #print("key:", key)
                    piece.row = key[0]
                    piece.col = key[1]
                    up = piece.row - 1
                    down = piece.row + 1
                    left = piece.col - 1
                    right = piece.col + 1
                    mandatory_capture = self.traverse_black(moves, piece, keys, up, down, left, right, mandatory_capture, skipped)
                    #print(mandatory_capture, skipped)
                    #print("keys:", keys)

        #print("moves:", moves)
        return moves, skipped

    def traverse_black(self, moves, piece, keys, up, down, left, right, mandatory_capture, skipped):
        is_left_up_empty, is_left_up_skip = self.check_up_left(up, left, 'BLACK')
        is_right_up_empty, is_right_up_skip = self.check_up_right(up, right, 'BLACK')
        is_left_down_empty, is_left_down_skip = self.check_down_left(down, left, 'BLACK')
        is_right_down_empty, is_right_down_skip = self.check_down_right(down, right, 'BLACK')
        mandatory_capture = mandatory_capture
        skipped = skipped
        moved = False

        if skipped == True:
            for i in range(len(moves[piece.row, piece.col])):
                if (piece.row-1, piece.col-1) == moves[piece.row, piece.col][i]:
                    is_left_up_skip = False
                    #print("YAY1")
                if (piece.row-1, piece.col+1) == moves[piece.row, piece.col][i]:
                    is_right_up_skip = False
                    #print("YAY2")
                if (piece.row+1, piece.col-1) == moves[piece.row, piece.col][i]:
                    is_left_down_skip = False
                    #print("YAY3")
                if (piece.row+1, piece.col+1) == moves[piece.row, piece.col][i]:
                    is_right_down_skip = False
                    #print("YAY4")

            copy_values = moves[piece.row, piece.col]
            #print("copy_values:", copy_values)
            #print(len(copy_values))

            keys.remove(tuple((piece.row, piece.col)))

        if is_left_down_empty == False and is_left_down_skip == True:
            #print("DOWN LEFT RED!")
            if skipped == True:
                moves[down+1, left-1] = [(down, left)]
                for i in range(len(copy_values)):
                    moves[down+1, left-1].append(tuple(copy_values[i]))
            else:
                moves[down+1, left-1] = [(down, left)]
            mandatory_capture = True
            moved = True
            keys.append(tuple((down+1, left-1)))
            #print(moves)
        
        if is_right_down_empty == False and is_right_down_skip == True:
            #print("DOWN RIGHT RED!")
            if skipped == True:
                moves[down+1, right+1] = [(down, right)]
                for i in range(len(copy_values)):
                    moves[down+1, right+1].append(tuple(copy_values[i]))
            else:
                moves[down+1, right+1] = [(down, right)]
            mandatory_capture = True
            moved = True
            keys.append(tuple((down+1, right+1)))
            #print(moves)

        if piece.colour == 'B':
            if is_left_up_empty == False and is_left_up_skip == True:
                #print("UP LEFT RED!")
                if skipped == True:
                    moves[up-1, left-1] = [(up, left)]
                    for i in range(len(copy_values)):
                        moves[up-1, left-1].append(tuple(copy_values[i]))
                else:
                    moves[up-1, left-1] = [(up, left)]
                mandatory_capture = True
                moved = True
                keys.append(tuple((up-1, left-1)))
                #print(moves)

            if is_right_up_empty== False and is_right_up_skip == True:
                #print("UP RIGHT RED!")
                if skipped == True:
                    moves[up-1, right+1] = [(up, right)]
                    for i in range(len(copy_values)):
                        moves[up-1, right+1].append(tuple(copy_values[i]))
                else:
                    moves[up-1, right+1] = [(up, right)]
                mandatory_capture = True
                moved = True
                keys.append(tuple((up-1, right+1)))
                #print(moves)

        if is_left_down_empty == True and is_left_down_skip == False and mandatory_capture == False:
            #print("DOWN LEFT EMPTY!")
            moves[down, left] = [(down, left)]

        if is_right_down_empty == True and is_right_down_skip == False and mandatory_capture == False:
            #print("DOWN RIGHT EMPTY!")
            moves[down, right] = [(down, right)]

        if piece.colour == 'B':            
            if is_left_up_empty == True and is_left_up_skip == False and mandatory_capture == False:
                #print("UP LEFT EMPTY!")
                moves[up, left] = [(up, left)]

            if is_right_up_empty == True and is_right_up_skip == False and mandatory_capture == False:
                #print("UP RIGHT EMPTY!")
                moves[up, right] = [(up, right)]

        if skipped == True and moved == True:
            del moves[piece.row, piece.col]

        #print("LOOP DONE")
        #print(moves)

        return mandatory_capture

    
    def check_up_left(self, up, left, colour):
        is_left_up_empty = False
        is_left_up_skip = False

        if (left >= 0 and up >= 0):
            if (self.board[up][left].colour == '0'):
                is_left_up_empty = True
            if (left - 1 >= 0 and up - 1 >= 0):
                if (colour == 'RED'):
                    if ((self.board[up][left].colour == 'b' or self.board[up][left].colour == 'B') and (self.board[up-1][left-1].colour == '0')):
                        is_left_up_skip = True
                if (colour == 'BLACK'):
                    if ((self.board[up][left].colour == 'r' or self.board[up][left].colour == 'R') and (self.board[up-1][left-1].colour == '0')):
                        is_left_up_skip = True

        return is_left_up_empty, is_left_up_skip

    def check_up_right(self, up, right, colour):
        is_right_up_empty = False
        is_right_up_skip = False

        if (right <= 7 and up >= 0):
            if (self.board[up][right].colour == '0'):
                is_right_up_empty = True
            if (right + 1 <= 7 and up - 1 >= 0):
                if (colour == 'RED'):
                    if ((self.board[up][right].colour == 'b' or self.board[up][right].colour == 'B') and (self.board[up-1][right+1].colour == '0')):
                        is_right_up_skip = True
                if (colour == 'BLACK'):
                    if ((self.board[up][right].colour == 'r' or self.board[up][right].colour == 'R') and (self.board[up-1][right+1].colour == '0')):
                        is_right_up_skip = True

        return is_right_up_empty, is_right_up_skip

    def check_down_left(self, down, left, colour):
        is_left_down_empty = False
        is_left_down_skip = False

        if (left >= 0 and down <= 7):
            if (self.board[down][left].colour == '0'):
                is_left_down_empty = True
            if (left - 1 >= 0 and down + 1 <= 7):
                if (colour == 'RED'):
                    if ((self.board[down][left].colour == 'b' or self.board[down][left].colour == 'B') and (self.board[down+1][left-1].colour == '0')):
                        is_left_down_skip = True
                if (colour == 'BLACK'):
                    if ((self.board[down][left].colour == 'r' or self.board[down][left].colour == 'R') and (self.board[down+1][left-1].colour == '0')):
                        is_left_down_skip = True

        return is_left_down_empty, is_left_down_skip

    def check_down_right(self, down, right, colour):
        is_right_down_empty = False
        is_right_down_skip = False

        if (right <= 7 and down <= 7):
            if (self.board[down][right].colour == '0'):
                is_right_down_empty = True
            if (right + 1 <= 7 and down + 1 <= 7):
                if (colour == 'RED'):
                    if ((self.board[down][right].colour == 'b' or self.board[down][right].colour == 'B') and (self.board[down+1][right+1].colour == '0')):
                        is_right_down_skip = True
                if (colour == 'BLACK'):
                    if ((self.board[down][right].colour == 'r' or self.board[down][right].colour == 'R') and (self.board[down+1][right+1].colour == '0')):
                        is_right_down_skip = True

        return is_right_down_empty, is_right_down_skip


class Piece:
    def __init__(self, row, col, colour):
        self.row = row
        self.col = col
        self.colour = colour
        self.king = False

        if self.colour == 'R' or self.colour == 'B':
            self.king = True

    def move_piece(self, new_row, new_col):
        self.row = new_row
        self.col = new_col

    def __repr__(self):
        return str(self.colour)

main()
