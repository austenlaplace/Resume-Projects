using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Laplace_Sudoku
{
    //Declaration of the Sudoku class - Sudoku.cs holds function and button definitions, while Sudoku.Designer.cs holds Winform object definitions
    //Files are united at compile time into the Sudoku class
    public partial class Sudoku : Form
    {
        //Declaration of variables used throughout the class

        //The playerBoxes variable is a 2D array of Textbox objects, in this case representing the sudoku board displayed to the user
        public TextBox[,] playerBoxes = new TextBox[9, 9];

        //The index variable is an integer, initalized to zero, that is used by the LoadPreloaded function to determine which stored board to load
        private int index = 0;

        //The getBoards variable is a list form of the 2D character array of the stored sudoku boards drawn from example.txt. It is used to call up
        //new boards during the LoadPreloaded function
        private List<char[,]> getBoards = new List<char[,]>();

        //The newBoard variable is a 2D array of characters and represents the raw values of the suduko board that are entered into the text boxes
        private char[,] newBoard = new char[9, 9];

        //Sudoku class construtor. Assigns the 81 Textbox objects to their equivalent playerBox array index
        public Sudoku()
        {
            InitializeComponent();
            //3x3 - The upper left square
            playerBoxes[0, 0] = textBox1;
            playerBoxes[1, 0] = textBox2;
            playerBoxes[2, 0] = textBox3;
            playerBoxes[0, 1] = textBox6;
            playerBoxes[1, 1] = textBox5;
            playerBoxes[2, 1] = textBox4;
            playerBoxes[0, 2] = textBox7;
            playerBoxes[1, 2] = textBox8;
            playerBoxes[2, 2] = textBox9;

            //3x3 - The upper center square
            playerBoxes[3, 0] = textBox18;
            playerBoxes[4, 0] = textBox17;
            playerBoxes[5, 0] = textBox16;
            playerBoxes[3, 1] = textBox15;
            playerBoxes[4, 1] = textBox14;
            playerBoxes[5, 1] = textBox13;
            playerBoxes[3, 2] = textBox10;
            playerBoxes[4, 2] = textBox11;
            playerBoxes[5, 2] = textBox12;

            //3x3 - The upper right square
            playerBoxes[6, 0] = textBox27;
            playerBoxes[7, 0] = textBox26;
            playerBoxes[8, 0] = textBox25;
            playerBoxes[6, 1] = textBox24;
            playerBoxes[7, 1] = textBox23;
            playerBoxes[8, 1] = textBox22;
            playerBoxes[6, 2] = textBox19;
            playerBoxes[7, 2] = textBox20;
            playerBoxes[8, 2] = textBox21;

            //3x3 - The middle left square
            playerBoxes[0, 3] = textBox36;
            playerBoxes[1, 3] = textBox35;
            playerBoxes[2, 3] = textBox34;
            playerBoxes[0, 4] = textBox33;
            playerBoxes[1, 4] = textBox32;
            playerBoxes[2, 4] = textBox31;
            playerBoxes[0, 5] = textBox28;
            playerBoxes[1, 5] = textBox29;
            playerBoxes[2, 5] = textBox30;

            //3x3 - The middle center square
            playerBoxes[3, 3] = textBox45;
            playerBoxes[4, 3] = textBox44;
            playerBoxes[5, 3] = textBox43;
            playerBoxes[3, 4] = textBox42;
            playerBoxes[4, 4] = textBox41;
            playerBoxes[5, 4] = textBox40;
            playerBoxes[3, 5] = textBox37;
            playerBoxes[4, 5] = textBox38;
            playerBoxes[5, 5] = textBox39;

            //3x3 - The middle right square
            playerBoxes[6, 3] = textBox54;
            playerBoxes[7, 3] = textBox53;
            playerBoxes[8, 3] = textBox52;
            playerBoxes[6, 4] = textBox51;
            playerBoxes[7, 4] = textBox50;
            playerBoxes[8, 4] = textBox49;
            playerBoxes[6, 5] = textBox46;
            playerBoxes[7, 5] = textBox47;
            playerBoxes[8, 5] = textBox48;

            //3x3 - The lower left square
            playerBoxes[0, 6] = textBox63;
            playerBoxes[1, 6] = textBox62;
            playerBoxes[2, 6] = textBox61;
            playerBoxes[0, 7] = textBox60;
            playerBoxes[1, 7] = textBox59;
            playerBoxes[2, 7] = textBox58;
            playerBoxes[0, 8] = textBox55;
            playerBoxes[1, 8] = textBox56;
            playerBoxes[2, 8] = textBox57;

            //3x3 - The lower center square
            playerBoxes[3, 6] = textBox72;
            playerBoxes[4, 6] = textBox71;
            playerBoxes[5, 6] = textBox70;
            playerBoxes[3, 7] = textBox69;
            playerBoxes[4, 7] = textBox68;
            playerBoxes[5, 7] = textBox67;
            playerBoxes[3, 8] = textBox64;
            playerBoxes[4, 8] = textBox65;
            playerBoxes[5, 8] = textBox66;

            //3x3 - The lower right square
            playerBoxes[6, 6] = textBox81;
            playerBoxes[7, 6] = textBox80;
            playerBoxes[8, 6] = textBox79;
            playerBoxes[6, 7] = textBox78;
            playerBoxes[7, 7] = textBox77;
            playerBoxes[8, 7] = textBox76;
            playerBoxes[6, 8] = textBox73;
            playerBoxes[7, 8] = textBox74;
            playerBoxes[8, 8] = textBox75;

        }

        //The checkButton_Click function contains the action the program should take if the user clicks the Check button
        private void checkButton_Click(object sender, EventArgs e)
        {
            //Declaration of local variables. bool? correct gets a nullable boolean value from the FinalCheck function, while bool isCorrect is set to true to check against correct
            bool? correct = false;
            bool isCorrect = true;

            //If the FinalCheck function does not return a value, inform the player that they havn't filled in all the board spaces.
            if (!FinalCheck().HasValue)
            {
                messageBox.Text = "You haven't filled in all the blanks";
            }

            //If the FinalCheck function returns a value, set correct equal to that value
            else
            {
                correct = FinalCheck();

                //Compare the values of correct and isCorrect. If both are true, inform the player that they have won the game.
                if (correct.GetValueOrDefault() == isCorrect & correct.HasValue)
                    messageBox.Text = "Congratulations, you've won!";

                //If the values of correct and isCorrect are not both true, inform the player that they need to keep solving the board
                else
                    messageBox.Text = "Incorrect board state. Keep going!";
            }
        }

        //The loadButton_Click function contains the actions the program should take if the user clicks the Load Preloaded button
        private void loadButton_Click(object sender, EventArgs e)
        {
            //If the getBoards list is empty, read in a list of predetermined boards from the example.txt file
            if (getBoards.Count == 0)
            {
                List<string> listOfBoards = new List<string>();
                using (StreamReader streamReader = new StreamReader(Application.StartupPath + "\\examples.txt"))
                {
                    string storedBoard;
                    while ((storedBoard = streamReader.ReadLine()) != null)
                        listOfBoards.Add(storedBoard);
                }

                //For each board read in from example.txt, generate a new 2D character array to hold the read in number values
                foreach (string storedBoard in listOfBoards)
                {
                    //The boardArray variable is a 2D character array that holds the read in board values from example.txt
                    char[,] boardArray = new char[9, 9];

                    //The for loops process the read in values. If the values are periods, change the relevant index to a blank space instead
                    for (int x_Index = 0; x_Index < 9; ++x_Index)
                    {
                        for (int y_Index = x_Index * 9; y_Index < x_Index * 9 + 9; ++y_Index)
                            boardArray[x_Index, y_Index % 9] = storedBoard[y_Index] != '.' ? storedBoard[y_Index] : ' ';
                    }

                    //Add the processed board to the getBoards list
                    getBoards.Add(boardArray);

                }
            }

            //Once all boards have been loaded into the getBoards list, call the LoadPreloaded function to load a board into the text boxes.
            //The LoadPreloaded function can be called as long as there are still boards in the list that have not been displayed.
            LoadPreloaded(getBoards[index]);
            ++index;
            if (index != getBoards.Count)
                return;

            index = 0;
        }

        //The LoadPreloaded function handles the display of predetermined boards loaded in from an outside file to the player
        private void LoadPreloaded(char[,] storedBoard)
        {
            //Set the newBoard array equal to the processed storedBoard passed to the LoadPreloaded function
            newBoard = storedBoard;
            messageBox.Text = "New game started! Good luck!";

            //The for loops handle displaying entries to the player. If the entry of an index isn't a space, make it unusable 
            //by the player so they can't modify preloaded number positions
            for(int x_Index = 0; x_Index < 9; ++x_Index)
            {
                for(int y_Index = 0; y_Index < 9; ++y_Index)
                {
                    playerBoxes[x_Index, y_Index].Text = newBoard[x_Index, y_Index].ToString();
                    playerBoxes[x_Index, y_Index].Enabled = true;

                    if (newBoard[x_Index, y_Index] != ' ')
                        playerBoxes[x_Index, y_Index].Enabled = false;
                }
            }
        }

        //Functions for checking the board

        //The ValidEntryCheck function checks that all entries on the board are valid  (Numbers 1 - 9 or blank spaces)
        private bool ValidEntryCheck(List<char> entries)
        {
            //The entryList variable is a List of characters that stores all valid entries the player has made on the board
            List<char> entryList = new List<char>();

            //For each charcter stored in the passed through list, if the entry isn't a blank space:
            //If the entry isn't an integer or the list contains the entry already, return false
            //Otherwise, add the entry to the entryList list
            foreach (char entry in entries)
            {
                if(entry != ' ')
                {
                    if (!int.TryParse(entry.ToString(), out int validEntry) || entryList.Contains(entry))
                        return false;

                    entryList.Add(entry);
                }
            }

            return true;
        }

        //The HorizontalCheck function checks the horizontal rows for valid Sudoku entries
        private bool HorizontalCheck(char[,] sudokuBoard)
        {
            //The for loops check every x index on a given y index (so for [x index, y index] -> [0 - 8, 1], [0 - 8, 2]...
            //and adds the passed in board indices to the entries list. Finally it checks the entries list with ValidEntryCheck,
            //which returns false if any of the entries are invalid
            for (int y_Index = 0; y_Index < 9; ++y_Index)
            {
                List<char> entries = new List<char>();

                for (int x_Index = 0; x_Index < 9; ++x_Index)
                {
                    entries.Add(sudokuBoard[x_Index, y_Index]);
                }

                if (!ValidEntryCheck(entries))
                    return false;
            }

            return true;
        }

        //The VerticalCheck function checks the vertical rows for valid Sudoku entries
        private bool VerticalCheck(char[,] sudokuBoard)
        {
            //The for loops check every y index on a given x index (so for [x index, y index] -> [0, 0 - 8], [1, 0 - 8]...
            //and adds the passed in board indices to the entries list. Finally it checks the entries list with ValidEntryCheck,
            //which returns false if any of the entries are invalid
            for (int x_Index = 0; x_Index < 9; ++x_Index)
            {
                List<char> entries = new List<char>();

                for (int y_Index = 0; y_Index < 9; ++y_Index)
                {
                    entries.Add(sudokuBoard[x_Index, y_Index]);
                }

                if (!ValidEntryCheck(entries))
                    return false;
            }

            return true;
        }

        //The SquaresCheck function checks the nine 3x3 squares of the Sudoku board for valid Sudoku entries
        private bool SquaresCheck(char[,] sudokuBoard)
        {
            //The outer two for loops check every y index on a given x index (so for [x index, y index] -> [0, 0 - 2], [1, 0 - 2]...
            //and adds the passed in board indices to the entries list. Note that the x and y values only go up to 2 instead of 8
            //since they will be multiplied by three in the inner for loops.

            //The inner two for loops check every y index times 3 for every x index times 3, until it reaches x times 3 plus three
            //to handle the base case of the x and y indices being zero. So for index [0, 0], it will check [0 - 2, 0 - 2]. 
            //Finally it checks the entries list with ValidEntryCheck, which returns false if any of the entries are invalid
            for (int x_Index = 0; x_Index < 3; ++x_Index)
            {
                for (int y_Index = 0; y_Index < 3; ++y_Index)
                {
                    List<char> entries = new List<char>();

                    for(int x_Times = x_Index * 3; x_Times < x_Index * 3 + 3; ++x_Times)
                    {
                        for(int y_Times = y_Index * 3; y_Times < y_Index * 3 + 3; ++y_Times)
                        {
                            entries.Add(sudokuBoard[x_Times, y_Times]);
                        }
                    }

                    if (!ValidEntryCheck(entries))
                        return false;
                }
            }

            return true;
        }

        //The nullable boolean function CheckCompleteBoard checks to see if all three board check functions are true
        private bool? CheckCompleteBoard(char[,] sudokoBoard)
        {
            //Logic of nullable boolean - return true IF HorizontalCheck AND VerticalCheck AND CheckSquares all return true
            //return false otherwise
            if (!HorizontalCheck(sudokoBoard) || !VerticalCheck(sudokoBoard) || !SquaresCheck(sudokoBoard))
            {
                return new bool?(false);
            }

            //The for loops check every y index on a given x index (so for [x index, y index] -> [0, 0 - 8], [1, 0 - 8]...
            //and then checks to see if any of the indices of the passed in board are still blank. If so, return false
            //If not, return true
            for (int x_Index = 0; x_Index < 9; ++x_Index)
            {
                for (int y_Index = 0; y_Index < 9; ++y_Index)
                {
                    if (sudokoBoard[x_Index, y_Index] == ' ')
                        return new bool?();
                }
            }

            return new bool?(true);
        }

        //The nullable boolean function FinalCheck converts the player entered values in the text boxes into the indices of a
        //2D array for processing by the CheckCompleteBoard function
        private bool? FinalCheck()
        {
            //The sudokuBoard 2D array will gather the player entered values in the textboxes and then be passed to the 
            //CheckCompleteBoard function
            char[,] sudokuBoard = new char[9, 9];

            //The for loops convert every y index on a given x index (so for [x index, y index] -> [0, 0 - 8], [1, 0 - 8]...
            //into the appropriate index in the sudokuBoard 2D array, then passes the array to the CheckCompleteBoard function
            for (int x_Index = 0; x_Index < 9; ++x_Index)
            {
                for (int y_Index = 0; y_Index < 9; ++y_Index)
                {
                    sudokuBoard[x_Index, y_Index] = playerBoxes[x_Index, y_Index].Text[0];
                }
            }

            return CheckCompleteBoard(sudokuBoard);
        }

        //The solveButton_Click function contains the actions the program should take if the user clicks the Solve button
        private void solveButton_Click(object sender, EventArgs e)
        {
            //The for loops check every y index on a given x index (so for [x index, y index] -> [0, 0 - 8], [1, 0 - 8]...
            //and converts the player entered values in the text boxes into the relevant indices in the newBoard 2D array
            for (int x_Index = 0; x_Index < 9; ++x_Index)
            {
                for (int y_Index = 0; y_Index < 9; ++y_Index)
                {
                    newBoard[x_Index, y_Index] = playerBoxes[x_Index, y_Index].Text[0];
                }
            }

            //The timeToSolve variable is used to calculate how long the board took the program to solve
            DateTime timeToSolve = DateTime.Now;
            if (SudokuSolve(newBoard))
            {
                //The for loops check every y index on a given x index (so for [x index, y index] -> [0, 0 - 8], [1, 0 - 8]...
                //and converts the the relevant indices in the newBoard 2D array into values in the text boxes associated with the indices
                for (int x_Index = 0; x_Index < 9; ++x_Index)
                {
                    for (int y_Index = 0; y_Index < 9; ++y_Index)
                    {
                        playerBoxes[x_Index, y_Index].Text = newBoard[x_Index, y_Index].ToString();
                    }
                }

                //If the board is solved, inform the user of the program's success and the total time taken to solve the board
                messageBox.Text = "Board solved in " + (DateTime.Now - timeToSolve).TotalSeconds + " seconds.";
            }

            //If the board is not solvable, inform the user
            else
                messageBox.Text = "Board not solvable in current state.";
        }

        //The solving algorithm was based on the one retrieved from:
        //https://codereview.stackexchange.com/questions/179725/sudoku-solver-recursive-solution-with-clear-structure
        //Modified to work with Winforms and predetermined boards instead of a single hardcoded board
        //Beginning of retrieved algorithm

        //The SudokuSolve function takes in a Sudoku board stored in a 2D array and then passes 
        //it the to SolveBoard function along with the inital indices for the SolveBoard function to start from
        public static bool SudokuSolve(char[,] board)
        {
            //Pass the passed in Suduko board and the initial index of [0,0] to the SolveBoard function
            return SolveBoard(board, 0, 0);
        }

        //The SolveBoard function recursively solves the passed in Sudoku board
        private static bool SolveBoard(char[,] board, int row, int column)
        {
            //If the passed in row number is > 8, the entire board has been evaluated
            if (row > 8)
                return true;

            //The visit variable is set to the board index passed in by the function.
            //The space variable is set to the value of visit when it is equal to a blank space
            var visit = board[row, column];
            var space = visit == ' ';

            var nextRow = column == 8 ? (row + 1) : row;
            var nextColumn = column == 8 ? 0 : (column + 1);

            if (!space)
                return SolveBoard(board, nextRow, nextColumn);

            //The availableNumbers variable gets the returned value of the getAvailableNumbers function
            var availableNumbers = getAvailableNumbers(board, row, column);

            //Recursive call of the SolveBoard function. If a solution is found, return true. Otherwise,
            //Continue calling the SolveBoard function with the iterated nextRow and nextColumn parameters
            foreach (var entry in availableNumbers)
            {
                board[row, column] = entry;

                var result = SolveBoard(board, nextRow, nextColumn);

                if (result)
                    return true;

                board[row, column] = ' ';
            }

            return false;
        }

        private static HashSet<char> getAvailableNumbers(char[,] board, int currentRow, int currentCol)
        {
            var numbers = new char[] { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
            var available = new HashSet<char>(numbers);

            //Check valid entries by row
            for (int col = 0; col < 9; col++)
            {
                var visit = board[currentRow, col];
                var isDigit = visit != ' ';

                if (isDigit)
                {
                    available.Remove(visit);
                }
            }

            //Check valid entries by column
            for (int row = 0; row < 9; row++)
            {
                var visit = board[row, currentCol];
                var isDigit = visit != ' ';

                if (isDigit)
                {
                    available.Remove(visit);
                }
            }

            //Check valid entries in the nine 3x3 squares
            var startRow = currentRow / 3 * 3;
            var startCol = currentCol / 3 * 3;
            for (int row = startRow; row < startRow + 3; row++)
            {
                for (int col = startCol; col < startCol + 3; col++)
                {
                    var visit = board[row, col];
                    var isDigit = visit != ' ';

                    if (isDigit)
                    {
                        available.Remove(visit);
                    }
                }
            }

            return available;
        }
        //End of retrieved algorithm

        //The newGameButton_Click function contains the actions the program will take if the user clicks the New Game button
        private void newGameButton_Click(object sender, EventArgs e)
        {
            //The for loops check every y index on a given x index (so for [x index, y index] -> [0, 0 - 8], [1, 0 - 8]...
            //and set every index to a blank space and enables the boxes for user interaction, then calls the CreateNewGame function
            for (int x_Index = 0; x_Index < 9; ++x_Index)
            {
                for (int y_Index = 0; y_Index < 9; ++y_Index)
                {
                    playerBoxes[x_Index, y_Index].Text = " ";
                    playerBoxes[x_Index, y_Index].Enabled = true;
                }
            }

            CreateNewGame();
        }

        //The CreateNewGame function creates a new, solvable Sudoku board from scratch
        private void CreateNewGame()
        {
            //Set the newBoard 2D array to be a new 2D array
            newBoard = new char[9, 9];

            //The for loops check every y index on a given x index (so for [x index, y index] -> [0, 0 - 8], [1, 0 - 8]...
            //in the array and fills the array with blank spaces
            for (int x_Index = 0; x_Index < 9; ++x_Index)
            {
                for (int y_Index = 0; y_Index < 9; ++y_Index)
                {
                    newBoard[x_Index, y_Index] = ' ';
                }
            }

            //The blank board is sent to the SudokuSolve function for processing. The SudokuSolve function
            //will create an entire solved Sudoku board
            SudokuSolve(newBoard);

            messageBox.Text = "New game started! Good luck!";

            //The generatedBoardValues variable is a list of tuples consisting of integer pairs.
            //It is set to equal the amount of entries that will be displayed to the player upon starting
            //a new game, in this case 20, that will be displayed by the SetNewBoardValues function
            List<Tuple<int, int>> generatedBoardValues = SetNewBoardValues(20);

            //The for loops check every y index on a given x index (so for [x index, y index] -> [0, 0 - 8], [1, 0 - 8]...
            //And then sets the tuples containing the x_Index, y_Index pairs to the values of the relevant index on the 
            //newly created and solved board
            for (int x_Index = 0; x_Index < 9; x_Index++)
            {
                for(int y_Index = 0; y_Index < 9; y_Index++)
                {
                    if (!generatedBoardValues.Any(generateValues =>
                    {
                        if (generateValues.Item1 == x_Index)
                            return generateValues.Item2 == y_Index;

                        return false;
                    }))

                        //All other spaces on the solved board are set to be blank spaces
                        newBoard[x_Index, y_Index] = ' ';

                    //If a given box contains a newly generated value, turn interactivity off so the player
                    //cannot modify the content of the box
                    else
                        playerBoxes[x_Index, y_Index].Enabled = false;
                }
            }

            //The for loops check every y index on a given x index (so for [x index, y index] -> [0, 0 - 8], [1, 0 - 8]...
            //and sets the relevant textboxes in the playerBoxes array to the indices in the newBoard array
            for (int x_Index = 0; x_Index < 9; ++x_Index)
            {
                for (int y_Index = 0; y_Index < 9; ++y_Index)
                {
                    playerBoxes[x_Index, y_Index].Text = newBoard[x_Index, y_Index].ToString();
                }
            }
        }

        //The SetNewBoardValues function generates new board values when called by the CreateNewGame function
        private List<Tuple<int, int>> SetNewBoardValues(int numberToGenerate)
        {
            //The newValues variable is a list of tuples containing the x and y indices of the newly generated values
            List<Tuple<int, int>> newValues = new List<Tuple<int, int>>();

            //The startGeneration variable is an integer initialized to zero to be a counter for the number of values generated
            int startGeneration = 0;

            //The randomNumber variable is a initialized to be a new random function variable
            Random randomNumber = new Random();

            //The do-while loop generates new values to be placed on the newly created board. The generatedBox variable is a 
            //tuple that contains a random x index between 0 and 9 and a random y index between 0 and 9
            //The if statement sets the tuples containing the x_Index, y_Index pairs to the values of the x and y indices 
            //of the generated tuple. Then it increments the startGeneration counter and adds the new tuple to the newValues
            //list. The loop will continue to execute until the startGeneration counter is equal to the numberToGenerate value
            //that was passed into the function, in this case 20
            do
            {
                Tuple<int, int> generatedBox = new Tuple<int, int>(randomNumber.Next(0, 9), randomNumber.Next(0, 9));

                if (!newValues.Any(generateValues =>
                 {
                     if (generateValues.Item1 == generatedBox.Item1)
                         return generateValues.Item2 == generatedBox.Item2;

                     return false;
                 }))
                {
                    ++startGeneration;
                    newValues.Add(generatedBox);
                }
            } while (startGeneration < numberToGenerate);

            return newValues;
        }

    }

}
