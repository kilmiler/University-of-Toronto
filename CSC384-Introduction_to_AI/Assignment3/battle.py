import sys

inputfile = sys.argv[1]
outputfile = sys.argv[2]

f = open(inputfile, 'r')
f.close
input_content = f.readlines()


def main():
    initial_game = Game()
    row_constraints = initial_game.get_row_constraints(input_content)
    col_constraints = initial_game.get_col_constraints(input_content)
    layout = initial_game.get_layout(input_content)
    initial_game.create_variables_from_input(layout)
    #print(initial_game.variables)
    #print(initial_game.variables[5][0])

    initial_game.create_domain_for_variable(initial_game.variables[5][0], row_constraints, col_constraints)

    for row in range(len(initial_game.variables)):
        for col in range(len(initial_game.variables)):
            domain = initial_game.create_domain_for_variable(initial_game.variables[row][col], row_constraints, col_constraints)
            initial_game.all_domains.append(domain)

    MRV_variable = initial_game.MRV(initial_game.variables)
    
    print(MRV_variable)

    ## CSP IMPLEMENTATION ## 
    ########################

    # Save to File "output#.txt"
    with open(outputfile, 'w') as f:
        for row in initial_game.variables:
            for variable in row:
                if(variable.type == '0'):
                    f.write("0")
                if(variable.type == 'S'):
                    f.write("S")
                if(variable.type == 'W'):
                    f.write("W")
                if(variable.type == 'L'):
                    f.write("L")
                if(variable.type == 'R'):
                    f.write("R")
                if(variable.type == 'T'):
                    f.write("T")
                if(variable.type == 'B'):
                    f.write("B")
                if(variable.type == 'M'):
                    f.write("M")
            f.write("\n")



class Game:
    def __init__(self):
        self.row_constraints = []
        self.col_constraints = []
        self.layout = []
        self.variables = []
        self.all_domains = []

    def get_row_constraints(self, input):
        for row in range(1):
            self.row_constraints.append(input[row])
        return self.row_constraints
    
    def get_col_constraints(self, input):
        for row in range(1, 2):
            self.col_constraints.append(input[row])
        return self.col_constraints


    def get_layout(self, input):
        for row in range(3, 9):
            self.layout.append(input[row])
            #print(row)
        return self.layout

    def create_variables_from_input(self, input):
        for row in range(6):
            self.variables.append([])
            for col in range(6):
                if input[row][col] == '0':
                    self.variables[row].append(Variable(row, col, '0'))    
                if input[row][col] == 'S':
                    self.variables[row].append(Variable(row, col, 'S'))  
                if input[row][col] == 'W':
                    self.variables[row].append(Variable(row, col, 'W'))  
                if input[row][col] == 'L':
                    self.variables[row].append(Variable(row, col, 'L'))  
                if input[row][col] == 'R':
                    self.variables[row].append(Variable(row, col, 'R'))
                if input[row][col] == 'T':
                    self.variables[row].append(Variable(row, col, 'T'))  
                if input[row][col] == 'B':
                    self.variables[row].append(Variable(row, col, 'B'))
                if input[row][col] == 'M':
                    self.variables[row].append(Variable(row, col, 'M'))

    def create_domain_for_variable(self, variable, row_constraints, col_constraints):
        up = variable.row - 1
        down = variable.row + 1
        right = variable.col + 1
        left = variable.col - 1
        up_up = ''
        up_left = ''
        up_right = ''
        down_down = ''
        down_left = ''
        down_right = ''
        left_left = ''
        right_right = ''
        row_constraint = row_constraints[0][variable.row]
        col_constraint = col_constraints[0][variable.col]
        around = []

        if(variable.row != 0):
            up_up = self.variables[up][variable.col].type
            around.append(up_up)
            if(variable.col != 0):
                up_left = self.variables[up][left].type
                around.append(up_left)
            if(variable.col != 5):
                up_right = self.variables[up][right].type
                around.append(up_right)

        if(variable.row != 5):
            down_down = self.variables[down][variable.col].type
            around.append(down_down)
            if(variable.col != 0):
                down_left = self.variables[down][left].type
                around.append(down_left)
            if(variable.col != 5):
                down_right = self.variables[down][right].type
                around.append(down_right)

        if(variable.col != 0):
            left_left = self.variables[variable.row][left].type
            around.append(left_left)
        
        if(variable.col != 5):
            right_right = self.variables[variable.row][right].type
            around.append(right_right)
        

        if(variable.type == '0'):
            if(up_up == 'B' or up_up == 'S'):
                variable.domain.append('W')
                return
            elif(down_down == 'T' or down_down == 'S'):
                variable.domain.append('W')
                return
            elif(left_left == 'R' or left_left == 'S'):
                variable.domain.append('W')
                return
            elif(right_right == 'L' or right_right == 'S'):
                variable.domain.append('W')
                return
            elif(up_left == 'B' or up_left == 'S' or up_left == 'M' or up_left == 'T' or up_left == 'L' or up_left == 'R'):
                variable.domain.append('W')
                return
            elif(up_right == 'B' or up_right == 'S' or up_right == 'M' or up_right == 'T' or up_right == 'L' or up_right == 'R'):
                variable.domain.append('W')
                return
            elif(down_left == 'B' or down_left == 'S' or down_left == 'M' or down_left == 'T' or down_left == 'L' or down_left == 'R'):
                variable.domain.append('W')
                return
            elif(down_right == 'B' or down_right == 'S' or down_right == 'M' or down_right == 'T' or down_right == 'L' or down_right == 'R'):
                variable.domain.append('W')
                return
            elif(up_up == 'T'):
                if(col_constraint <= 2):
                    variable.domain.append('B')
                    return
                elif(down_down == 'B'):
                    variable.domain.append('M')
                    return
            elif(up_up == 'M'):
                if(col_constraint <= 3):
                    variable.domain.append('B')
                    return
                elif(down_down == 'B'):
                    variable.domain.append('M')
                    return
            elif(down_down == 'B'):
                if(col_constraint <= 2):
                    variable.domain.append('T')
                    return
            elif(down_down == 'M'):
                if(col_constraint <=3):
                    variable.domain.append('T')
                    return
                elif(up_up == 'T'):
                    variable.domain.append('M')
                    return
            elif(left_left == 'L'):
                if(row_constraint == 2):
                    variable.domain.append('R')
                    return
                elif(right_right == 'R'):
                    variable.domain.append('M')
                    return
            elif(left_left == 'M'):
                if(row_constraint <= 3):
                    variable.domain.append('R')
                    return
                elif(right_right == 'R'):
                    variable.domain.append('M')
                    return
            elif(right_right == 'R'):
                if(row_constraint == 2):
                    variable.domain.append('L')
                    return
            elif(right_right == 'M'):
                if(row_constraint <= 3):
                    variable.domain.append('L')
                    return
                elif(left_left == 'L'):
                    variable.domain.append('M')
                    return
            else:
                variable.domain.append('S')
                variable.domain.append('W')
        else:
            variable.domain.append(variable.type)
        
        print(variable.domain)


    def MRV(self, variables):
        curr_min = 100
        min_variable = ''
        for row in range(len(variables)):
            #print(row)
            for variable in range(len(variables)):
                #print(variable)
                if(len(variables[row][variable].domain) < curr_min):
                    curr_min = curr_min
                    min_variable = variables[row][variable]
        
        return min_variable        
    




class Variable:
    def __init__(self, row, col, type):
        self.row = row
        self.col = col
        self.type = type
        self.domain = []
    
    def __repr__(self):
        return str(self.type)


main()