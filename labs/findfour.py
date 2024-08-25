
# Lab 02, Find Four, by Ben Adelman
# Grade: 8/10


def get_initial_board(rows: int, columns: int) -> list[list[str]]:
    board =[]
    for i in range(0,rows):
        board.append(["."]*columns)
    return board


def print_board(board: list[list[str]]):
    print("")
    print(" "+"_" * (len(board[0])*2))
    for row in board:
        print("|", end="")
        for x in row:
            print(x+" ", end="")
        print("|")
    print(" "+"-" * ((len(board[0])*2)-1))


def is_board_full(board: list[list[str]]):
    for i in board:
        for j in i:
            if j == ".":
                return False
    return True


def insert_chip(board: list[list[str]], column: int, chip: str) -> int:
    for x in reversed(range(0,len(board))):
        if board[x][column] == ".":
            return x


def is_win_state(chip: str, board: list[list[str]], row: int, column: int) -> bool:
    for x in range(max(0, column - 3), min(len(board[0]) - 3, column)):
        if (board[row][x] == chip and board[row][x + 1] == chip and board[row][x + 2] == chip and board[row][x + 3] == chip):
            return True
    for y in range(max(0, row - 3), min(len(board) - 3, row)):
        if (board[y][column] == chip and board[y + 1][column] == chip and board[y + 2][column] == chip and board[y + 3][column] == chip):
            return True

    return False


def main():
    print("Welcome to Find Four!")
    print("---------------------")
    height = input("Enter height of board (rows): ")
    while not height.isdigit() or not (4 <= int(height) <= 25):
        if int(height) < 4:
            print("Error: height must be at least 4!")
        elif int(height) > 25:
            print("Error: height must be at most 25!")
        elif not height.isdigit():
            print("Error: not a number!")
        height = input("Enter height of board (rows): ")
    width = input("Enter width of board (columns): ")
    while not width.isdigit() or not (4 <= int(width) <= 25):
        if int(width) < 4:
            print("Error: width must be at least 4!")
        elif int(width) > 25:
            print("Error: width must be at most 25!")
        elif not width.isdigit():
            print("Error: not a number!")
        print(" ")
        width = input("Enter width of board (columns): ")
    board = get_initial_board(int(height),int(width))
    print_board(board)
    game = True
    key = {"1":"x","2":"o"}
    print("\nPlayer 1: x")
    print("\nPlayer 2: o")
    while game:
        for i in ["1","2"]: # key so dont have to write this out twice
            if is_board_full(board) and game:
                game = False
                print("Draw game! Players tied.")
            if game:
                p1 = input(f"\nPlayer {i} - Select a Column: ")
                while not p1.isdigit():
                    print("Error: not a number!")
                    p1 = input(f"Player {i} - Select a Column: ")
                while (int(p1) < 0) or (int(p1) > int(width)):
                    print("Error: no such column!")
                    p1 = input(f"Player {i} - Select a Column: ")
                while board[0][int(p1)] != ".":
                    print("Error: column is full!")
                    p1 = input(f"Player {i} - Select a Column: ")
                row = insert_chip(board,int(p1),key[i])
                board[row][int(p1)] = key[i] # because reversed in func, need to do len minus row minus 1
                print("")
                print_board(board)
                for y in range(0,len(board)):
                    for z in range(0,len(board[0])):
                        if is_win_state(key[i],board,y,z):
                            game = False
                if not game:
                    print(f"\nPlayer {i} won the game!")


if __name__ == "__main__":
    main()
