import java.util.ArrayList;
import java.util.Scanner;

public class floodit {
    private static ArrayList<Tile> cluster; //to store the visited/already selected tiles

    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        ArrayList<Tile[][]> gridList = new ArrayList<>(); //for storing all cases, to read input first

        int cases = Integer.parseInt(scanner.nextLine());

        for(int i = 0; i < cases; i++) //for all cases
        {
            int length = Integer.parseInt(scanner.nextLine()); //take the length of the array
            Tile[][] grid = new Tile[length][length]; //create new grid

            for(int j = 0; j < length; j++)
            {
                String temp = scanner.nextLine();
                for(int n = 0; n < length; n++)
                {
                    int color = temp.charAt(n) - '0'; //save the color
                    Tile tile = new Tile(j, n, color); //create a tile with coordinates and color
                    grid[j][n] = tile; //store it in its place in the grid
                }
            }
            gridList.add(grid); //add to list for later processing
        }

        for(int i = 0; i < cases; i++)
        {
            playGame(gridList.get(i)); //play the game
        }



    }

    private static void playGame(Tile[][] grid)
    {
        cluster = new ArrayList<>(); //initialize clusterlist
        int[] colorOccurences = new int[6]; //for keeping track of how many times the colors occur
        int totalChanges = 0; //for keeping track of total changes of color
        int currentColor = grid[0][0].color; //fetch the color from the origin tile

        grid[0][0].setVisited(true); //set it as visited
        cluster.add(grid[0][0]); //add it to the cluster
        expandCluster(grid, grid[0][0].color); //expand the cluster (if there is more of the same color connected to the origin

        while (cluster.size() < (grid.length * grid.length)) //while the cluster is smaller than the number of tiles on the grid
        {
            int nextColor = findNextColor(currentColor, grid); //find the next color
            colorOccurences[nextColor - 1]++; //increment the corresponding element in the array for keeping track of the color occurences
            expandCluster(grid, nextColor); //expand the cluster with the next color
            totalChanges++; //increment total changes
            currentColor = nextColor; //set the current color to nextColor for next iteration
        }

        System.out.println(totalChanges); //print all changes
        for(int i = 0; i < colorOccurences.length; i++)
        {
            System.out.print(colorOccurences[i] + " "); //print how many times a color was chosen
        }
        System.out.println();

    }

    private static void expandCluster(Tile[][] grid, int newColor)
    {
        for(int i = 0; i < cluster.size(); i++) //for each tile in the current cluster
        {
            Tile coordinate = cluster.get(i); //get the tile
            grid[coordinate.x][coordinate.y].setColor(newColor); //set the color to the new color

            if(validateIndex(coordinate.x - 1, coordinate.y, grid.length)) //make sure index over is ok
            {
                exploreAndAddToCluster(coordinate.x - 1, coordinate.y, newColor, grid); //explore the element over and add to cluster
            }

            if(validateIndex(coordinate.x, coordinate.y - 1, grid.length)) //make sure index to the left is ok
            {
                exploreAndAddToCluster(coordinate.x, coordinate.y - 1, newColor, grid); //explore the element to the left and add to cluster
            }

            if(validateIndex(coordinate.x, coordinate.y + 1, grid.length)) //make sure index to the right is ok
            {
                exploreAndAddToCluster(coordinate.x, coordinate.y + 1, newColor, grid); //explore the element to the right and add to cluster
            }

            if(validateIndex(coordinate.x + 1, coordinate.y, grid.length)) //make sure index under is ok
            {
                exploreAndAddToCluster(coordinate.x + 1, coordinate.y, newColor, grid); //explore the element under and add to cluster
            }
        }
    }

    private static void exploreAndAddToCluster(int x, int y, int newColor, Tile[][] grid)
    {
        if(!validateIndex(x, y, grid.length)) //make sure index is ok, if not return
        {
            return;
        }
        if(grid[x][y].color != newColor || grid[x][y].visited) //make sure that it is the color we are looking for and that it has not been visited
        {
            return; //if not return
        }
        grid[x][y].setVisited(true); //set it to visited, to avoid double calculation
        cluster.add(grid[x][y]); //add it to the cluster

        exploreAndAddToCluster(x, y - 1, newColor, grid); //recursive call for the element to the left
        exploreAndAddToCluster(x - 1, y, newColor, grid); //recursive call for the element over
        exploreAndAddToCluster(x + 1, y, newColor, grid); //recursive call for the element under
        exploreAndAddToCluster(x, y + 1, newColor, grid); //recursive call for the element to the right
    }

    private static int findNextColor(int oldColor, Tile[][] grid)
    {

        int[] colorOccurences = new int[6]; //array for keeping track of how many neighbors with what color
        Tile[][] gridCopy = getGridCopy(grid); //make a copy of the grid, to be able to set tiles as visited temporarily

        for(int i = 0; i < cluster.size(); i++) //for each tile in the current cluster
        {
            Tile coordinate = cluster.get(i); //get the tile at i

            /*
            The code below checks the indexes over, under, to the left and to the right,
            then it fetches it's color if the index was valid, after this, explores its neighbors
            to find subclusters and adds their size to the corresponding place in the array
             */

            if(validateIndex(coordinate.x - 1, coordinate.y, grid.length))
            {
                int color = grid[coordinate.x - 1][coordinate.y].color;
                colorOccurences[color - 1] += exploreNeighbors(coordinate.x - 1 , coordinate.y, color, gridCopy);
            }

            if(validateIndex(coordinate.x, coordinate.y - 1, grid.length))
            {
                int color = grid[coordinate.x][coordinate.y - 1].color;
                colorOccurences[color - 1] += exploreNeighbors(coordinate.x , coordinate.y - 1, color, gridCopy);
            }

            if(validateIndex(coordinate.x, coordinate.y + 1, grid.length))
            {
                int color = grid[coordinate.x][coordinate.y + 1].color;
                colorOccurences[color - 1] += exploreNeighbors(coordinate.x, coordinate.y + 1, color, gridCopy);
            }

            if(validateIndex(coordinate.x + 1, coordinate.y, grid.length))
            {
                int color = grid[coordinate.x + 1][coordinate.y].color;
                colorOccurences[color - 1] += exploreNeighbors(coordinate.x + 1 , coordinate.y, color, gridCopy);
            }
        }

        return findMaxIndex(colorOccurences, oldColor) + 1; //find the index (color - 1) for the index with the maximum occurences

    }
    private static int exploreNeighbors(int x, int y, int color, Tile[][] grid)
    {
        if(!validateIndex(x, y, grid.length)) //if index is not valid, return
        {
            return 0;
        }
        if(grid[x][y].color != color || grid[x][y].visited) //check if the color is the same or if it's already visited
        {
            return 0; //if so, return
        }

        int neighborsWithSameColor = 0;
        grid[x][y].setVisited(true); //set element to visited

        neighborsWithSameColor += exploreNeighbors(x, y - 1, color, grid); //recursive call on the element to the left
        neighborsWithSameColor += exploreNeighbors(x - 1, y, color, grid); //recursive call on the element over
        neighborsWithSameColor += exploreNeighbors(x + 1, y, color, grid); //recursive call on the element under
        neighborsWithSameColor += exploreNeighbors(x, y + 1, color, grid); //recursive call on the element to the right

        return 1 + neighborsWithSameColor; //return neighbors with same color (sub-cluster size) together with self



    }

    private static int findMaxIndex(int[] colorOccurences, int currentColor)
    {
        int max = -1;
        int indexToReturn = -1;

        for (int i = 0; i < colorOccurences.length; i++) { //for each color
            if (colorOccurences[i] > max && (i != currentColor - 1)) { //if the color occurence is greater than max, and i is not corresponding to the current color
                max = colorOccurences[i]; //set max to colorOccurences for comparison
                indexToReturn = i; //index to return is set to i
            }
            if((colorOccurences[i] == max) && (i != currentColor - 1)) //if color occurences is the same as max and i is not the current color
            {
                if(i < indexToReturn) //check if i is less than the current index to return
                {
                    indexToReturn = i;
                }
            }
        }

        return indexToReturn;
    }
    private static boolean validateIndex(int x, int y, int length)
    {
        return (x >= 0) && (y >= 0) && (x < length) && (y < length); //check that it is not out of range
    }

    private static Tile[][] getGridCopy(Tile[][] grid) //this is just for making a deep copy of the grid for temporary visit-marking
    {
        Tile[][] copy = new Tile[grid.length][grid.length];
        for(int i = 0; i < grid.length; i++)
        {
            for (int j = 0; j < grid.length; j++) {
                Tile tile = new Tile(grid[i][j].x, grid[i][j].y, grid[i][j].color);
                copy[i][j] = tile;
            }
        }
        return copy;
    }

    static class Tile
    {
        int x, y, color;
        boolean visited = false;


        public Tile(int x, int y, int color)
        {
            this.x = x;
            this.y = y;
            this.color = color;
        }


        public void setVisited(boolean visited) {
            this.visited = visited;
        }

        public void setColor(int color) {
            this.color = color;
        }
    }


}