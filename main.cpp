#include <iostream>
#include <vector>
using namespace std;

class Matrix {
public:
	void setMatrix()
	{
		int size;
		cout << "Choose the dimensions of your matrix:"; //Dimensions
		cin >> size;
		matrix.resize(size, vector<double>(size));
		for (size_t i = 0; i < size; i++)
		{
			cout << endl;
			for (size_t j = 0; j < size; j++)
			{
				cout << "Enter element: ";
				cin >> matrix[i][j];
			}
		}
	}
	vector<vector<double> > getMatrix() const {
		return matrix;
	}
	float determinant(vector<vector<double> > mat) {
		//Recursion Base Case
		if (mat.size() == 2)
		{
			return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
		}
		else
		{
			vector<vector<vector<double> > > minors = minor(mat); //Gets an array of minor matrices of the matrix
			double sum = 0;	//Total Sum of the determinant
			double current = 0;
			int k = 0;	//Used to iterate over the columns of the matrix mat, each column has an associated minor
			while (k < mat.size()) //the number of cofactors that the matrix will have is the amount of columns
				//since its square # of rows = # of columns, each value of k is one minor
			{
				if (k % 2 == 1) //Uses cofactors of first row so the sign is determined by + - + -... convention
				{
					mat[0][k] = -mat[0][k]; //If it is an odd-indexed column (since the first column is index 0), the sign is negative
				}
				//Adds the value of the matrix cell * it's determinat of the minor to the sum
				sum+=mat[0][k] * determinant(minors[k]); 
				k++;	//Go to the next column
			}	
			return sum;
		}
	}
	vector<vector<vector<double> > > minor(vector<vector<double> > mat) {
		int k = mat.size();//Makes k the size of the matrix as it holds each minor of the first row
		vector<vector<vector<double> > > minors;
		minors.resize(k);  //Resize the 3D vector to size k - so it will hold k amount of 2d vectors (The minors)
		for (size_t i = 0; i < k; i++)
		{
			minors[i].resize(mat.size() - 1); //Resizes the rows of the matrix to one less than the size of the matrix
			for (size_t j = 0; j < minors[i].size(); j++)
			{
				minors[i][j].resize(mat.size() - 1); //Resizes the columns of the matrix to one less than the size of the matrix
			}
		}

		int row, column;
		row = column = 0;
		k = 0;
		while (k < mat.size())
		{
			for (int i = 1; i < mat.size(); i++) //starts at 1 since we cross out the first row for all minors (puts us on row 2)
			{
				for (int j = 0; j < mat[i].size(); j++)//We evaluate every column tho
				{
					if (j != k) //Basically, the minor #k would cross out column j so whenever they arent the same, store that element
					{
						minors[k][row][column] = mat[i][j]; 
						column++;
					}
				}	
				row++;
				column = 0;
			}
			k++;
			row = column = 0;
		}
		return minors; //Returns all the minors as one 3D vector
	}
private:
	vector<vector<double> >matrix;
};

int main()
{
	Matrix mat;
	mat.setMatrix();
	cout << "Determinant is: " << mat.determinant(mat.getMatrix());
}
