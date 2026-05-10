#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool isCycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    printf("candidate_count: %i\n", candidate_count);
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    printf("------vote-----------\n");
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            printf("%i %i\n", rank, i);
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // printf("-----record_preferences------------\n");
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // printf("Before Updation: i: %i j: %i ranks[i]: %i ranks[j]: %i preferences[][]:
            // %i\n", i, j, ranks[i], ranks[j], preferences[ranks[i]][ranks[j]]);
            preferences[ranks[i]][ranks[j]]++;
            // printf("preferences[%i][%i]: %i\n\n", ranks[i], ranks[j],
            //      preferences[ranks[i]][ranks[j]]);
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // printf("------add_pairs-----------\n");
    for (int i = 0, k = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                // printf("k: %i pairs[%i].winner: %i pairs[%i].loser: %i\n", k, k, pairs[k].winner,
                // k,
                //      pairs[k].loser);
                pairs[k].winner = i;
                pairs[k].loser = j;
                // printf("k: %i pairs[%i].winner: %i pairs[%i].loser: %i\n\n", k, k,
                // pairs[k].winner,
                //      k, pairs[k].loser);
                k++;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                // printf("k: %i pairs[%i].winner: %i pairs[%i].loser: %i\n", k, k, pairs[k].winner,
                // k,
                //      pairs[k].loser);
                pairs[k].winner = j;
                pairs[k].loser = i;
                // printf("k: %i pairs[%i].winner: %i pairs[%i].loser: %i\n\n", k, k,
                // pairs[k].winner,
                //      k, pairs[k].loser);
                k++;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // printf("------sort_pairs-----------\n");

    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] <
                preferences[pairs[j].winner][pairs[j].loser])
            {
                // printf("Before swap: i: %i pairs[%i].winner: %i pairs[%i].loser: %i\n", i, i,
                //      pairs[i].winner, i, pairs[i].loser);
                // printf("Before swap: j: %i pairs[%i].winner: %i pairs[%i].loser: %i\n", j, j,
                //      pairs[j].winner, j, pairs[j].loser);

                int tempWinner = pairs[i].winner;
                int tempLoser = pairs[i].loser;

                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;

                pairs[j].winner = tempWinner;
                pairs[j].loser = tempLoser;

                // printf("After swap: i: %i pairs[%i].winner: %i pairs[%i].loser: %i\n", i, i,
                //      pairs[i].winner, i, pairs[i].loser);
                // printf("After swap: j: %i pairs[%i].winner: %i pairs[%i].loser: %i\n", j, j,
                //      pairs[j].winner, j, pairs[j].loser);
            }
        }
    }

    // for(int i = 0; i < pair_count; i++) {
    //     printf("pairs[%i].winner: %i\n", i, pairs[i].winner);
    //     printf("pairs[%i].loser: %i\n", i, pairs[i].loser);
    //     printf("---\n");
    // }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // printf("--------lock_pairs---------\n");
    for (int i = 0; i < pair_count; i++)
    {
        if (!(isCycle(pairs[i].winner, pairs[i].loser)))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            // printf("locked[%i][%i] is marked true\n\n", pairs[i].winner, pairs[i].loser);
        }
    }
    return;
}

bool isCycle(int winner, int loser)
{
    // printf("--------isCycle---------\n");
    if (winner == loser)
    {
        // printf("winner = loser\n");
        return true;
    }

    for (int i = loser, j = 0; j < candidate_count; j++)
    {
        // printf("locked[%i][%i]: %i\n", i, j, locked[i][j]);
        if (locked[i][j] == true)
        {
            if (isCycle(winner, j) == true)
            {
                return true;
            }
        }
    }

    // printf("No cycle detected\n");
    return false;
}

void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            // printf("locked[%i][%i]: %i\n", j, i, locked[j][i]);
            if (locked[j][i] == true)
            {
                winner = false;
                break;
            }
        }
        if (winner == true)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
