import tkinter as tk
import tkinter.messagebox
import random

#Luokka pelille
class TTT:
    def __init__(self):
        self.window = tk.Tk()
        self.window.title("Ristinolla")
        self.board = [' '] * 9
        self.player = 'X'
        self.buttons = []

        #Luodaan ruudut
        for i in range(3):
            for j in range(3):
                button = tk.Button(self.window, text='', font=('Normal', 20), width=8, height=3,
                                   command=lambda row=i, col=j: self.on_click(row, col))
                button.grid(row=i, column=j)
                self.buttons.append(button)

    #Pelaajan valinta
    def on_click(self, row, col):
        if self.board[3 * row + col] == ' ':
            self.board[3 * row + col] = self.player
            self.buttons[3 * row + col].config(text=self.player, state='disabled', disabledforeground='blue')
            if self.check_winner():
                self.show_winner()
            elif ' ' not in self.board:
                self.show_draw()
            else:
                self.player = 'O' if self.player == 'X' else 'X'
                if self.player == 'O':
                    self.computer_move()

    #Tietokoneen valinta
    def computer_move(self):
        empty_cells = [i for i, cell in enumerate(self.board) if cell == ' ']
        if empty_cells:
            index = self.minimax(self.board, 'O')['index']
            self.board[index] = 'O'
            self.buttons[index].config(text='O', state='disabled', disabledforeground='red')
            if self.check_winner():
                self.show_winner()
            elif ' ' not in self.board:
                self.show_draw()
            else:
                self.player = 'X'

    #Voittajan tarkastus
    def check_winner(self):
        for i in range(3):
            if self.board[i] == self.board[i + 3] == self.board[i + 6] != ' ':
                return True
            if self.board[3 * i] == self.board[3 * i + 1] == self.board[3 * i + 2] != ' ':
                return True
        if self.board[0] == self.board[4] == self.board[8] != ' ':
            return True
        if self.board[2] == self.board[4] == self.board[6] != ' ':
            return True
        return False

    #Näyttää voittajan 
    def show_winner(self):
        if self.player == 'X':
            winner = 'Pelaaja'
        else:
            winner = 'Tietokone'
        tk.messagebox.showinfo("Ristinolla", f" {winner} voitti!")
        self.reset_game()

    #Näyttää tasapelin
    def show_draw(self):
        tk.messagebox.showinfo("Ristinolla", "Tasapeli!")
        self.reset_game()

    #Restoi pelin
    def reset_game(self):
        for button in self.buttons:
            button.config(text='', state='normal')
        self.board = [' '] * 9
        self.player = 'X'
        
    #AI joka laskee tietokoneelle optimaalisen siirron
    def minimax(self, new_board, player):
        available_spots = [i for i, spot in enumerate(new_board) if spot == ' ']

        if self.check_winner() and player == 'O':
            return {'score': 1}
        elif self.check_winner() and player == 'X':
            return {'score': -1}
        elif not available_spots:
            return {'score': 0}

        moves = []

        for spot in available_spots:
            move = {}
            move['index'] = spot
            new_board[spot] = player

            if player == 'X':
                result = self.minimax(new_board, 'O')
                move['score'] = result['score']
            else:
                result = self.minimax(new_board, 'X')
                move['score'] = result['score']

            new_board[spot] = ' '

            moves.append(move)

        if player == 'X':
            best_move = max(moves, key=lambda x: x['score'])
        else:
            best_move = min(moves, key=lambda x: x['score'])
        return best_move

    #Pelin aloitus
    def run(self):
        self.window.mainloop()

#Pelin käynnistys
if __name__ == "__main__":
    game = TTT()
    game.run()

