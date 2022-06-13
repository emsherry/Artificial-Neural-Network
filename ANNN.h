#include <iostream>
#include <math.h>
#include <time.h>
#include <fstream>
using namespace std;

// Applying ANN with the module  9-3-1

class ANN
{
private:
    double input_nodes[9];
    double input_weights[9][3];
    double hidden_nodes[3];
    double hidden_weights[3];
    double hidden_errors[3];
    string temp1;
    double output_node;
    double target_value[958];
    double error;
    double learning_rate;
    double inputval[958][9];

public:
    ANN()
    {
        input_nodes[9] = 0;
        //Giving randomn weights for the input nodes
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                input_weights[i][j] = (double)(rand() / (double)RAND_MAX * 2) - 1;
            }
        }
        //Giving randomn weights for the output nodes
        for (int i = 0; i < 3; i++)
        {
            hidden_weights[i] = (double)(rand() / (double)RAND_MAX * 2) - 1;
        }

        //Reading file to train data
        ifstream input("tic-tac-toe.data", ios::in);
        if (!input)
        {
            cout << "File could not be opened!";
        }
        else
        {
            for (int k = 0; k < 958; k++)
            {
                input >> temp1;

                int j = 0;
                for (int i = 0; i < 19; i++)
                {

                    if (temp1[i] == ',')
                    {
                        continue;
                    }
                    else if (temp1[i] == 'x')
                    {
                        inputval[k][j] = 1;
                        j++;
                    }
                    else if (temp1[i] == 'o')
                    {
                        inputval[k][j] = -1;
                        j++;
                    }
                    else if (temp1[i] == 'b')
                    {
                        inputval[k][j] = 0;
                        j++;
                    }
                    else if (temp1[i] == 'p')
                    {
                        target_value[k] = 1;
                    }
                    else if (temp1[i] == 'n')
                        target_value[k] = 0;
                }
            }
        }

        output_node = 0;
        error = 0;
        learning_rate = 0.1;

        //Closing filee
        input.close();
    }

    double activation_function(double sigmoid)
    {
        sigmoid = 1 / (1 + exp(-1 * sigmoid));
        return sigmoid;
    }
 //Function used to train data
    void forward_feed()
    {
        //Calculating hidden nodes through forward feed
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                hidden_nodes[j] += input_nodes[i] * input_weights[i][j];
            }
        }

        //Applying activation function on nodes to give the required value 
        //Thhe activation function used here is Sigmoid function
        for (int i = 0; i < 3; i++)
        {
            hidden_nodes[i] = activation_function(hidden_nodes[i]);
        }

        //Calculating output 
        for (int j = 0; j < 3; j++)
        {
            output_node += hidden_nodes[j] * hidden_weights[j];
        }
        output_node = activation_function(output_node);
        // cout << endl << output_node;
    }

///Function used to use ANN for the board passed
    void forward_feed(double *input)
    {
        //Calculating forward feed for the board passed while playing
        for (int i = 0; i < 9; i++)
        {
            input_nodes[i] = input[i];
        }
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                hidden_nodes[j] += input_nodes[i] * input_weights[i][j];
            }
        }
        for (int i = 0; i < 3; i++)
        {
            hidden_nodes[i] = activation_function(hidden_nodes[i]);
        }

        for (int j = 0; j < 3; j++)
        {
            output_node += hidden_nodes[j] * hidden_weights[j];
        }

        //Applying Activation Funtion(Sigmoid)
        output_node = activation_function(output_node);
      
    }

    void back_propagation(double targetval)
    {

        // Error Calculation for output node
        error = targetval - output_node;

        // Calculatiing Errors for hidden weights
        for (int i = 0; i < 3; i++)
        {
            hidden_errors[i] = error * hidden_weights[i];
        }

        // Correcting Hidden weights
        for (int i = 0; i < 3; i++)
        {
            hidden_weights[i] = hidden_weights[i] + (learning_rate * error * (output_node * (1 - output_node)) * output_node);
        }

        // Correcting input weights
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                input_weights[i][j] = input_weights[i][j] + (learning_rate * hidden_errors[j] * (hidden_nodes[j] * (1 - hidden_nodes[j])) * hidden_nodes[j]);
            }
        }
    }
    
    //Training the data through the file being read
    void training()
    {
        int no_of_iterations = 100000;
        for (int i = 0; i < no_of_iterations; i++)
        {
            int r = rand() % 958;
            forward_feed(inputval[r]);
            // cout << r << " = " << output_node << endl;
            if (abs(target_value[r] - output_node) < 0.1)
                break;
            back_propagation(target_value[r]);
        }
    }

//Setting input nodes again and agian while playing
    void setInputNodes(double **board)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
                this->input_nodes[i*3+j] = board[i][j];
        }
    }

    double getoutput()
    {
        return this->output_node;
    }
};
