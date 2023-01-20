# from ctypes import sizeof
from ast import AsyncFunctionDef
from queue import Empty
import numpy as np
import sys

from state import State
from agent import Agent


# outputfile = ''
inputfile = sys.argv[1]

# f = open('/Users/hee/Documents/UT/Y4/Fall(4-1)/384/Assignment2/checkers_validate/input0.txt', 'r')
f = open(inputfile, 'r')
f.close
input_content = f.read().splitlines() 


def main():
    initial_board = [[*row] for row in input_content]

    state = State(board=initial_board.copy())
    print('original board')
    print(state)
    agent = Agent()
    actions = agent.get_actions(state, agent.player_color)

    for action in actions:
        result = State(board=state.board)
        result.set_state(action.moves, action.start_piece)
        print('-----')
        print(action)
        print(result)

main()
