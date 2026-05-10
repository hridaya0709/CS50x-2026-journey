#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
int findNextVote(int voter, int candidate);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }

        printf("--------------\n\n");
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            // printf("voter: %i rank: %i i: %i\n", voter, rank, i);
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    int j = 0;
    for (int i = 0; i < voter_count; i++)
    {
        if (candidates[preferences[i][j]].eliminated)
        {
            // printf("If candidate eliminated i: %i j: %i name: %s\n", i, j,
            // candidates[preferences[i][j]].name);
            int j1 = findNextVote(i, j);
            candidates[preferences[i][j1]].votes++;
            // printf("Candidate eliminated votes: %i j1: %i name: %s\n",
            // candidates[preferences[i][j1]].votes, j1, candidates[preferences[i][j1]].name);
        }
        else
        {
            // printf("Candidate not eliminated i: %i j: %i name: %s\n", i, j,
            // candidates[preferences[i][j]].name);
            candidates[preferences[i][j]].votes++;
            // printf("Candidate not eliminated votes: %i\n", candidates[preferences[i][j]].votes);
        }
    }
    return;
}

int findNextVote(int voter, int candidate)
{
    int nextPreference = 0;

    // printf("findNextVote name: %s %i\n", candidates[preferences[voter][candidate + 1]].name,
    //  candidates[preferences[voter][candidate + 1]].eliminated);
    if (candidates[preferences[voter][candidate + 1]].eliminated)
    {
        // printf("If next candidate is eliminated too name: %s\n",
        // candidates[preferences[voter][candidate + 1]].name);
        nextPreference = findNextVote(voter, candidate + 1);
    }
    else
    {
        // printf("If next candidate is not eliminated name: %s\n",
        // candidates[preferences[voter][candidate + 1]].name);
        nextPreference = candidate + 1;
    }

    // printf("Return from findNextVote name: %s nextPreference: %i\n",
    //  candidates[preferences[voter][nextPreference]].name, nextPreference);
    return nextPreference;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    int highestVotes = (int) ceil(voter_count / 2.0);
    // printf("%i\n", highestVotes);
    int winnerCount = 0;
    string winner;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!(candidates[i].eliminated))
        {
            if (candidates[i].votes > highestVotes)
            {
                // printf("Current winner i: %i %s\n", i, candidates[i].name);
                winnerCount = 1;
                winner = candidates[i].name;
            }
        }
    }
    if (winnerCount == 1)
    {
        printf("%s\n", winner);
        return true;
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int min = MAX_VOTERS;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!(candidates[i].eliminated) && min > candidates[i].votes)
        {
            min = candidates[i].votes;
        }
    }
    // printf("Min votes: %i\n", min);
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (!(candidates[i].eliminated) && !(candidates[i].votes == min))
        {
            // printf("Inside is_tie %i %s %i\n", candidates[i].votes, candidates[i].name,
            //  candidates[i].eliminated);
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
            // printf("Eliminated: %s\n", candidates[i].name);
        }
    }
    return;
}
