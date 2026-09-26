#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
void case1_game1_instructions(void) {
    printf("\n--- HOW TO PLAY ---\n");
    printf("1. A list of numbers shows up. One number is your TARGET.\n");
    printf("2. Type the target's position in the list (1st number = 1, 2nd = 2, etc.)\n");
    printf("3. Stuck? Type 0 for a free hint. It won't be counted as wrong.\n");
    printf("4. Too many wrong guesses = round over.\n");
    printf("5. Answer fast and without hints to earn bonus points.\n");
    printf("6. Each round the list gets a bit bigger.\n");
    printf("-------------------\n\n");
}
int case1_game1_calcPoints(double t) {
    int p = 100 - (int)(t * 5);
    if (p < 10) p = 10;
    return p;
}
int case1_game1_contains(int *arr, int n, int val) 
{
	int i;
    for (i = 0; i < n; i++)
        if (arr[i] == val) return 1;
    return 0;
}
void case1_game1_fillUnique(int *arr, int n) {
	int i;
    for (i = 0; i < n; i++) {
        int v;
        do {
            v = rand() % 1000;
        } while (case1_game1_contains(arr, i, v));
        arr[i] = v;
    }
}
void case1_game1_playGame(int diff) {
    srand((unsigned)time(NULL));
    int startSize[3] = {10, 15, 20};
    int step[3]       = {3, 4, 5};
    int maxSize[3]    = {25, 35, 45};
    int maxTries[3]   = {4, 3, 2};

    int size = startSize[diff - 1];
    int round = 1, totalScore = 0, streak = 0, bestStreak = 0;

    while (size <= maxSize[diff - 1]) {
        int *arr = (int *)malloc(size * sizeof(int));
        case1_game1_fillUnique(arr, size);

        int idx = rand() % size;
        int target = arr[idx];

        printf("\nRound %d (size %d)\n", round, size);
        printf("List: ");
        int i;
        for (i = 0; i < size; i++)
            printf("%d ", arr[i]);
        printf("\nFind position of: %d  (0 = hint)\n", target);

        time_t start = time(NULL);
        int tries = 0, correct = 0, pos, usedHint = 0, firstGuess = 1;

        while (tries < maxTries[diff - 1]) {
            printf("Enter position: ");
            if (scanf("%d", &pos) != 1) {
                while (getchar() != '\n');
                continue;
            }

            if (pos == 0) {
                usedHint = 1;
                int mid = size / 2;
                if (idx < mid) printf("Hint: it's in the FIRST half of the list.\n");
                else printf("Hint: it's in the SECOND half of the list.\n");
                continue;
            }

            if (pos >= 1 && pos <= size && arr[pos - 1] == target) {
                correct = 1;
                break;
            }
            tries++;
            firstGuess = 0;
            printf("Wrong! Tries left: %d\n", maxTries[diff - 1] - tries);
        }

        if (!correct) {
            printf("\n%d wrong tries. GAME OVER.\n", maxTries[diff - 1]);
            printf("Final Score: %d | Best streak: %d\n", totalScore, bestStreak);
            free(arr);
            return;
        }

        double elapsed = difftime(time(NULL), start);
        int pts = case1_game1_calcPoints(elapsed);

        if (!usedHint && firstGuess) {
            streak++;
            if (streak >= 3) {
                int bonus = 15 * (streak - 2);
                pts += bonus;
                printf("Combo x%d! Bonus +%d\n", streak, bonus);
            }
        } else {
            streak = 0;
        }
        if (streak > bestStreak) bestStreak = streak;

        totalScore += pts;
        printf("Correct! Time: %.1f sec | Points: %d | Total: %d\n", elapsed, pts, totalScore);

        free(arr);
        round++;
        size += step[diff - 1];
    }

    printf("\nYou cleared all rounds!\nFinal Score: %d | Best streak: %d\n", totalScore, bestStreak);
}
void case1_game1_run(void) {
    int choice, diff = 2;
    do {
        printf("\n===== NUMBER SPOTTER =====\n");
        printf("1. Start Game\n");
        printf("2. Instructions\n");
        printf("3. Change difficulty (now: %s)\n", diff == 1 ? "Easy" : diff == 2 ? "Normal" : "Hard");
        printf("4. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: case1_game1_playGame(diff); break;
            case 2: case1_game1_instructions(); break;
            case 3:
                printf("Select difficulty - 1.Easy 2.Normal 3.Hard: ");
                if (scanf("%d", &diff) != 1 || diff < 1 || diff > 3) diff = 2;
                printf("Difficulty set.\n");
                break;
            case 4: printf("Bye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
}
void case1_game2_clearInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void case1_game2_waitRandom(int minMs, int maxMs) {
    int waitMs = minMs + rand() % (maxMs - minMs);
    clock_t startTime = clock();
    while (((clock() - startTime) * 1000 / CLOCKS_PER_SEC) < waitMs);
}
void case1_game2_run(void) {
    int choice, rounds = 0, i, played = 0, streak = 0, bestStreak = 0;
    int score, totalScore = 0, diff = 2;
    int minWait[3] = {2000, 1000, 400};
    int maxWait[3] = {4000, 3000, 1500};
    int lightning[3] = {200, 150, 100};
    int sharp[3]     = {400, 300, 200};
    int steady[3]    = {650, 500, 350};
    int slow[3]      = {1000, 900, 600};
    double ms, times[20], best, worst, sum, avg, range;
    clock_t t1, t2;

    srand((unsigned)time(NULL));

    do {
        printf("\n===== REACTION TIMER =====\n");
        printf("1. Play rounds\n");
        printf("2. View stats\n");
        printf("3. Change difficulty (now: %s)\n", diff == 1 ? "Easy" : diff == 2 ? "Normal" : "Hard");
        printf("4. Reset session\n");
        printf("5. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) { case1_game2_clearInput(); choice = 0; continue; }
        case1_game2_clearInput();

        switch (choice) {
            case 1:
                printf("How many rounds (1-20)? ");
                if (scanf("%d", &rounds) != 1) rounds = 0;
                case1_game2_clearInput();

                if (rounds < 1 || rounds > 20) {
                    printf("Invalid round count. Setting to 5.\n");
                    rounds = 5;
                }

                for (i = 0; i < rounds; i++) {
                    if (played >= 20) {
                        printf("Session full. Reset to continue.\n");
                        break;
                    }

                    printf("\nRound %d - get ready...\n", played + 1);
                    fflush(stdout);
                    case1_game2_waitRandom(minWait[diff - 1], maxWait[diff - 1]);

                    printf(">>> PRESS ENTER NOW! <<<\n");
                    fflush(stdout);

                    t1 = clock();
                    case1_game2_clearInput();
                    t2 = clock();

                    ms = (double)(t2 - t1) * 1000.0 / CLOCKS_PER_SEC;
                    times[played] = ms;

                    if (ms < lightning[diff - 1]) {
                        score = 120;
                        printf("Lightning fast! %.0f ms\n", ms);
                        streak++;
                    } else if (ms < sharp[diff - 1]) {
                        score = 80;
                        printf("Sharp. %.0f ms\n", ms);
                        streak++;
                    } else if (ms < steady[diff - 1]) {
                        score = 45;
                        printf("Steady. %.0f ms\n", ms);
                        streak = 0;
                    } else if (ms < slow[diff - 1]) {
                        score = 15;
                        printf("A bit slow. %.0f ms\n", ms);
                        streak = 0;
                    } else {
                        score = 5;
                        printf("Drifted off? %.0f ms\n", ms);
                        streak = 0;
                    }

                    if (streak >= 3) {
                        int bonus = 20;
                        score += bonus;
                        printf("Streak x%d! Bonus +%d\n", streak, bonus);
                    }
                    if (streak > bestStreak) bestStreak = streak;

                    totalScore += score;
                    played++;
                    printf("Round score: %d | Total: %d\n", score, totalScore);
                }
                break;

            case 2:
                if (played == 0) {
                    printf("No rounds played yet.\n");
                } else {
                    sum = 0;
                    best = times[0];
                    worst = times[0];
                    for (i = 0; i < played; i++) {
                        sum += times[i];
                        if (times[i] < best) best = times[i];
                        if (times[i] > worst) worst = times[i];
                    }
                    avg = sum / played;
                    range = worst - best;

                    printf("\n--- SESSION STATS ---\n");
                    printf("Rounds       : %d\n", played);
                    printf("Best         : %.0f ms\n", best);
                    printf("Worst        : %.0f ms\n", worst);
                    printf("Average      : %.0f ms\n", avg);
                    printf("Best streak  : %d\n", bestStreak);
                    printf("Score        : %d\n", totalScore);

                    if (range < 80) {
                        if (avg < 250) printf("Consistency: locked in\n");
                        else printf("Consistency: steady but slow\n");
                    } else if (range < 200) {
                        printf("Consistency: mostly even\n");
                    } else {
                        if (avg > 500) printf("Consistency: scattered, low focus\n");
                        else printf("Consistency: spiky, attention wandering\n");
                    }
                }
                break;

            case 3:
                printf("Select difficulty - 1.Easy 2.Normal 3.Hard: ");
                if (scanf("%d", &diff) != 1 || diff < 1 || diff > 3) diff = 2;
                case1_game2_clearInput();
                printf("Difficulty set. Hard = shorter wait + tighter timing to score well. Easy = longer wait + looser timing.\n");
                break;

            case 4:
                played = 0;
                totalScore = 0;
                streak = 0;
                bestStreak = 0;
                printf("Session reset.\n");
                break;

            case 5:
                printf("Final score: %d\n", totalScore);
                break;

            default:
                printf("Invalid option.\n");
        }
    } while (choice != 5);
}
void case2_game1_run(void) {
    int choice, answer, score, total = 0;
    clock_t start, end;
    double reactionTime;
    printf("\n");
    printf("*************\n");
    printf("*                                     *\n");
    printf("*        WORD SCRAMBLE GAME           *\n");
    printf("*                                     *\n");
    printf("*************\n");
    printf("\n+-------------------------------------+\n");
    printf("|          GAME MENU                  |\n");
    printf("+-------------------------------------+\n");
    printf("|  7  -> Start Game                   |\n");
    printf("|  0  -> Exit Game                    |\n");
    printf("+-------------------------------------+\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    if(choice == 7)
    {
        printf("\n=======================================\n");
        printf("          GAME STARTED!\n");
        printf("=======================================\n");
        printf("\n---------------------------------------\n");
        printf(" Q1  Scrambled Word: PPALE\n");
        printf("---------------------------------------\n");
        printf(" 1. APPLE\n");
        printf(" 2. MANGO\n");
        printf(" 3. BALL\n");
        printf(" 4. TIGER\n");
        start = clock();
        printf("\nYour Answer: ");
        scanf("%d", &answer);
        end = clock();
        reactionTime = (double)(end - start) / CLOCKS_PER_SEC;
        if(answer == 1)
        {
            score = 99;
            printf("\n>> Correct Answer! +99\n");
        }
        else
        {
            score = 0;
            printf("\n>> Wrong Answer!\n");
        }
        printf(">> Reaction Time: %.2f seconds\n", reactionTime);
        total = total + score;
        printf("\n---------------------------------------\n");
        printf(" Q2  Scrambled Word: RATWE\n");
        printf("---------------------------------------\n");
        printf(" 1. HOUSE\n");
        printf(" 2. WATER\n");
        printf(" 3. TABLE\n");
        printf(" 4. CHAIR\n");
        start = clock();
        printf("\nYour Answer: ");
        scanf("%d", &answer);
        end = clock();
        reactionTime = (double)(end - start) / CLOCKS_PER_SEC;
        if(answer == 2)
        {
            score = 99;
            printf("\n>> Correct Answer! +99\n");
        }
        else
        {
            score = 0;
            printf("\n>> Wrong Answer!\n");
        }
        printf(">> Reaction Time: %.2f seconds\n", reactionTime);
        total = total + score;
        printf("\n---------------------------------------\n");
        printf(" Q3  Scrambled Word: OHSOCL\n");
        printf("---------------------------------------\n");
        printf(" 1. SCHOOL\n");
        printf(" 2. COLLEGE\n");
        printf(" 3. OFFICE\n");
        printf(" 4. MARKET\n");
        start = clock();
        printf("\nYour Answer: ");
        scanf("%d", &answer);
        end = clock();
        reactionTime = (double)(end - start) / CLOCKS_PER_SEC;
        if(answer == 1)
        {
            score = 99;
            printf("\n>> Correct Answer! +99\n");
        }
        else
        {
            score = 0;
            printf("\n>> Wrong Answer!\n");
        }
        printf(">> Reaction Time: %.2f seconds\n", reactionTime);
        total = total + score;
        printf("\n---------------------------------------\n");
        printf(" Q4  Scrambled Word: NPE\n");
        printf("---------------------------------------\n");
        printf(" 1. CAR\n");
        printf(" 2. PEN\n");
        printf(" 3. BOX\n");
        printf(" 4. BAG\n");
        start = clock();
        printf("\nYour Answer: ");
        scanf("%d", &answer);
        end = clock();
        reactionTime = (double)(end - start) / CLOCKS_PER_SEC;
        if(answer == 2)
        {
            score = 99;
            printf("\n>> Correct Answer! +99\n");
        }
        else
        {
            score = 0;
            printf("\n>> Wrong Answer!\n");
        }
        printf(">> Reaction Time: %.2f seconds\n", reactionTime);
        total = total + score;
        printf("\n---------------------------------------\n");
        printf(" Q5  Scrambled Word: KOBO\n");
        printf("---------------------------------------\n");
        printf(" 1. BOOK\n");
        printf(" 2. PEN\n");
        printf(" 3. BAG\n");
        printf(" 4. DESK\n");
        start = clock();
        printf("\nYour Answer: ");
        scanf("%d", &answer);
        end = clock();
        reactionTime = (double)(end - start) / CLOCKS_PER_SEC;
        if(answer == 1)
        {
            score = 99;
            printf("\n>> Correct Answer! +99\n");
        }
        else
        {
            score = 0;
            printf("\n>> Wrong Answer!\n");
        }
        printf(">> Reaction Time: %.2f seconds\n", reactionTime);
        total = total + score;
        printf("\n\n***************\n");
        printf("*           GAME COMPLETED            *\n");
        printf("*************\n");
        printf("\n       YOUR FINAL SCORE\n");
        printf("       --------------\n");
        printf("       %d / 495\n", total);
        if(total == 495)
            printf("\n       PERFECT SCORE!\n");
        else if(total >= 297)
            printf("\n       GREAT JOB!\n");
        else
            printf("\n       KEEP PRACTICING!\n");
        printf("\n=======================================\n");
        printf("        THANK YOU FOR PLAYING!\n");
        printf("=======================================\n");
    }
    else if(choice == 0)
    {
        printf("\n=======================================\n");
        printf("       Game Ended. Goodbye!\n");
        printf("=======================================\n");
    }
    else
    {
        printf("\nInvalid Choice! Please run the game again.\n");
    }
    return;
}
void case2_game2_run(void) {
    int choice, answer, score, total = 0;
    clock_t start, end;
    double reactionTime;
    printf("================================\n");
    printf("          QUIZ GAME\n");
    printf("================================\n");
    printf("\nPress 7 to start the game\n");
    printf("Press 0 to quit the game\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    if(choice == 7)
    {
        printf("\nGame Started!\n");
        printf("\nQ1. Which language is used for C programming?\n");
        printf("1. Python\n");
        printf("2. C\n");
        printf("3. HTML\n");
        printf("4. Java\n");
        start = clock();
        printf("Enter your answer: ");
        scanf("%d", &answer);
        end = clock();
        reactionTime = (double)(end - start) / CLOCKS_PER_SEC;
        if(answer == 2)
        {
            score = 99;
            printf("Correct!\n");
        }
        else
        {
            score = 0;
            printf("Wrong Answer!\n");
        }
        printf("Reaction Time = %.2f seconds\n", reactionTime);
        printf("Score = %d\n", score);
        total = total + score;
        printf("\nQ2. Which function is used to print output in C?\n");
        printf("1. scanf()\n");
        printf("2. printf()\n");
        printf("3. input()\n");
        printf("4. print()\n");
        start = clock();
        printf("Enter your answer: ");
        scanf("%d", &answer);
        end = clock();
        reactionTime = (double)(end - start) / CLOCKS_PER_SEC;
        if(answer == 2)
        {
            score = 99;
            printf("Correct!\n");
        }
        else
        {
            score = 0;
            printf("Wrong Answer!\n");
        }
        printf("Reaction Time = %.2f seconds\n", reactionTime);
        printf("Score = %d\n", score);
        total = total + score;
        printf("\nQ3. Which data type stores an integer?\n");
        printf("1. float\n");
        printf("2. char\n");
        printf("3. int\n");
        printf("4. double\n");
        start = clock();
        printf("Enter your answer: ");
        scanf("%d", &answer);
        end = clock();
        reactionTime = (double)(end - start) / CLOCKS_PER_SEC;
        if(answer == 3)
        {
            score = 99;
            printf("Correct!\n");
        }
        else
        {
            score = 0;
            printf("Wrong Answer!\n");
        }
        printf("Reaction Time = %.2f seconds\n", reactionTime);
        printf("Score = %d\n", score);
        total = total + score;
        printf("\nQ4. Which symbol ends a C statement?\n");
        printf("1. :\n");
        printf("2. ;\n");
        printf("3. .\n");
        printf("4. ,\n");
        start = clock();
        printf("Enter your answer: ");
        scanf("%d", &answer);
        end = clock();
        reactionTime = (double)(end - start) / CLOCKS_PER_SEC;
        if(answer == 2)
        {
            score = 99;
            printf("Correct!\n");
        }
        else
        {
            score = 0;
            printf("Wrong Answer!\n");
        }
        printf("Reaction Time = %.2f seconds\n", reactionTime);
        printf("Score = %d\n", score);
        total = total + score;
        printf("\nQ5. Which loop is used for repetition in C?\n");
        printf("1. for\n");
        printf("2. if\n");
        printf("3. switch\n");
        printf("4. break\n");
        start = clock();
        printf("Enter your answer: ");
        scanf("%d", &answer);
        end = clock();
        reactionTime = (double)(end - start) / CLOCKS_PER_SEC;
        if(answer == 1)
        {
            score = 99;
            printf("Correct!\n");
        }
        else
        {
            score = 0;
            printf("Wrong Answer!\n");
        }
        printf("Reaction Time = %.2f seconds\n", reactionTime);
        printf("Score = %d\n", score);
        total = total + score;
        printf("\n================================\n");
        printf("         QUIZ COMPLETED\n");
        printf("================================\n");

        printf("Total Score = %d / 495\n", total);
    }
    else if(choice == 0)
    {
        printf("\nGame Ended.\n");
    }
    else
    {
        printf("\nInvalid Choice!\n");
    }
    return;
}
void case3_game1_run(void) {
    int choice;
    int score = 0;
    printf("=================================\n");
    printf("       WORD PICTURE MATCHING\n");
    printf("=================================\n\n");
    printf("Match each word with the correct picture.\n\n");
    printf("Pictures:\n");
    printf("1.  [APPLE]\n");
    printf("2.  [CAR]\n");
    printf("3.  [DOG]\n");
    printf("4.  [SUN]\n");
    printf("5.  [BOOK]\n");
    printf("6.  [BALL]\n");
    printf("7.  [TREE]\n");
    printf("8.  [HOUSE]\n");
    printf("9.  [FISH]\n");
    printf("10. [CHAIR]\n");
    printf("11. [CAT]\n");
    printf("12. [PEN]\n");
    printf("13. [FLOWER]\n");
    printf("14. [BIRD]\n");
    printf("15. [TABLE]\n");
    printf("16. [CLOCK]\n");
    printf("17. [PHONE]\n");
    printf("18. [CUP]\n");
    printf("19. [SHOES]\n");
    printf("20. [BOTTLE]\n\n");
    printf("=================================\n");
    printf("             ROUND 1\n");
    printf("=================================\n\n");
    printf("Question 1\n");
    printf("Word: HOUSE\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 8)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! HOUSE is picture number 8.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("Question 2\n");
    printf("Word: APPLE\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! APPLE is picture number 1.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("Question 3\n");
    printf("Word: CLOCK\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 16)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! CLOCK is picture number 16.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("Question 4\n");
    printf("Word: DOG\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 3)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! DOG is picture number 3.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("Question 5\n");
    printf("Word: CUP\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 18)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! CUP is picture number 18.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("=================================\n");
    printf("             ROUND 2\n");
    printf("=================================\n\n");
    printf("Question 6\n");
    printf("Word: BIRD\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 14)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! BIRD is picture number 14.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("Question 7\n");
    printf("Word: CAR\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 2)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! CAR is picture number 2.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("Question 8\n");
    printf("Word: FLOWER\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 13)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! FLOWER is picture number 13.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("Question 9\n");
    printf("Word: BALL\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 6)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! BALL is picture number 6.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("Question 10\n");
    printf("Word: PHONE\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 17)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! PHONE is picture number 17.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("=================================\n");
    printf("             ROUND 3\n");
    printf("=================================\n\n");
    printf("Question 11\n");
    printf("Word: SUN\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 4)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! SUN is picture number 4.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("Question 12\n");
    printf("Word: TABLE\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 15)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! TABLE is picture number 15.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("Question 13\n");
    printf("Word: CAT\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 11)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! CAT is picture number 11.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("Question 14\n");
    printf("Word: BOTTLE\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 20)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! BOTTLE is picture number 20.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("Question 15\n");
    printf("Word: TREE\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 7)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! TREE is picture number 7.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("=================================\n");
    printf("             ROUND 4\n");
    printf("=================================\n\n");
    printf("Question 16\n");
    printf("Word: SHOES\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 19)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! SHOES is picture number 19.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("Question 17\n");
    printf("Word: PEN\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 12)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! PEN is picture number 12.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("Question 18\n");
    printf("Word: BOOK\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 5)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! BOOK is picture number 5.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("Question 19\n");
    printf("Word: FISH\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 9)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! FISH is picture number 9.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("Question 20\n");
    printf("Word: CHAIR\n");
    printf("Enter the picture number: ");
    scanf("%d", &choice);
    if (choice == 10)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice >= 1 && choice <= 20)
    {
        printf("Wrong! CHAIR is picture number 10.\n\n");
    }
    else
    {
        printf("Invalid choice!\n\n");
    }
    printf("=================================\n");
    printf("       THANK YOU FOR COMING!\n");
    printf("=================================\n\n");

    printf("=================================\n");
    printf("          GAME OVER!\n");
    printf("=================================\n");
    printf("Your Score: %d/20\n", score);
    return;
}
void case3_game2_run(void) {
    int choice;
    int score = 0;

    printf("========================================\n");
    printf("       SENTENCE COMPLETION GAME\n");
    printf("========================================\n\n");
    printf("Complete the sentence by choosing the correct word \n");
    printf("Enter the number of your answer \n\n");
	printf("\n\n Question 1\n\n");
    printf("1: The boy is drinking ____ \n");
    printf("   1: Water\n");
    printf("   2: Running\n");
    printf("   3: Blue\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 2)
    {
        printf("Wrong! The correct answer is Water \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is Water \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n Question 2\n\n");
    printf("2: The cat is sleeping ____ the chair \n");
    printf("   1: On\n");
    printf("   2: Running\n");
    printf("   3: Quickly\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 2)
    {
        printf("Wrong! The correct answer is On \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is On \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n Question 3\n\n");
    printf("3: Riya went to school ____ she finished breakfast:\n");
    printf("   1: Because\n");
    printf("   2: After\n");
    printf("   3: Blue\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 2)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 1)
    {
        printf("Wrong! The correct answer is After \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is After \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n Question 4\n\n");
    printf("4: I stayed at home ____ it was raining:\n");
    printf("   1: Because\n");
    printf("   2: Before\n");
    printf("   3: Quickly\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 2)
    {
        printf("Wrong! The correct answer is Because \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is Because \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n Question 5\n\n");
    printf("5: ____ the teacher entered the class, the students became quiet.\n");
    printf("   1: Before\n");
    printf("   2: When\n");
    printf("   3: Although\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 2)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 1)
    {
        printf("Wrong! The correct answer is When \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is When \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n Question 6\n\n");
    printf("6: The girl is ____ a book.\n");
    printf("   1: Reading\n");
    printf("   2: Red\n");
    printf("   3: Slowly\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 2)
    {
        printf("Wrong! The correct answer is Reading \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is Reading \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n Question 7\n\n");
    printf("7: The dog ran ____ the garden.\n");
    printf("   1: In\n");
    printf("   2: Happy\n");
    printf("   3: Eat\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 2)
    {
        printf("Wrong! The correct answer is In \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is In \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n Question 8\n\n");
    printf("8: I brush my teeth ____ I go to bed.\n");
    printf("   1: Before\n");
    printf("   2: Blue\n");
    printf("   3: Running\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 2)
    {
        printf("Wrong! The correct answer is Before \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is Before \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n Question 9\n\n");
    printf("9: She was tired, ____ she continued studying.\n");
    printf("   1: But\n");
    printf("   2: Water\n");
    printf("   3: Tall\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 2)
    {
        printf("Wrong! The correct answer is But \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is But \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n Question 10\n\n");
    printf("10: We went outside ____ the rain stopped.\n");
    printf("   1: After\n");
    printf("   2: Green\n");
    printf("   3: Singing\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 2)
    {
        printf("Wrong! The correct answer is After \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is After \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n Question 11\n\n");
    printf("11: The baby is crying ____ she is hungry.\n");
    printf("   1: Because\n");
    printf("   2: Quickly\n");
    printf("   3: Yellow\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 2)
    {
        printf("Wrong! The correct answer is Because \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is Because \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n Question 12\n\n");
    printf("12: He walked ____ to school.\n");
    printf("   1: Slowly\n");
    printf("   2: Apple\n");
    printf("   3: Blue\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 2)
    {
        printf("Wrong! The correct answer is Slowly \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is Slowly \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n Question 13\n\n");
    printf("13: The children played ____ the park.\n");
    printf("   1: In\n");
    printf("   2: Hungry\n");
    printf("   3: Sleep\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 2)
    {
        printf("Wrong! The correct answer is In \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is In \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n Question 14\n\n");
    printf("14: I will call you ____ I reach home.\n");
    printf("   1: When\n");
    printf("   2: Red\n");
    printf("   3: Eating\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 2)
    {
        printf("Wrong! The correct answer is When \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is When \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n Question 15\n\n");
    printf("15: She wore a jacket ____ it was cold.\n");
    printf("   1: Because\n");
    printf("   2: Running\n");
    printf("   3: Green\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 2)
    {
        printf("Wrong! The correct answer is Because \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is Because \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n  Question 16\n\n");
    printf("16: The teacher gave us homework ____ the class ended.\n");
    printf("   1: Before\n");
    printf("   2: Blue\n");
    printf("   3: Quickly\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 2)
    {
        printf("Wrong! The correct answer is Before \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is Before \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n Question 17\n\n");
    printf("17: Rahul was hungry, ____ he ate a sandwich.\n");
    printf("   1: So\n");
    printf("   2: Tall\n");
    printf("   3: Sleeping\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 2)
    {
        printf("Wrong! The correct answer is So \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is So \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n Question 18\n\n");
    printf("18: The bird flew ____ the tree.\n");
    printf("   1: Over\n");
    printf("   2: Happy\n");
    printf("   3: Eating\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 2)
    {
        printf("Wrong! The correct answer is Over \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is Over \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n Question 19\n\n");
    printf("19: We stayed inside ____ it was raining heavily.\n");
    printf("   1: Because\n");
    printf("   2: Before\n");
    printf("   3: Slowly\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 2)
    {
        printf("Wrong! The correct answer is Because \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is Because \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n Question 20\n\n");
    printf("20: I finished my homework ____ I watched television.\n");
    printf("   1: Before\n");
    printf("   2: Blue\n");
    printf("   3: Running\n");
    printf("Enter your answer: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Correct!\n\n");
        score++;
    }
    else if (choice == 2)
    {
        printf("Wrong! The correct answer is Before \n\n");
    }
    else if (choice == 3)
    {
        printf("Wrong! The correct answer is Before \n\n");
    }
    else
    {
        printf("Invalid choice \n\n");
    }
    printf("\n\n   FINAL RESULT\n\n");
    printf("========================================\n");
    printf("             GAME RESULT\n");
    printf("========================================\n");
    printf("Your score is: %d out of 20\n", score);
    if (score == 20)
    {
        printf("Excellent! You answered all sentences correctly \n");
    }
    else if (score >= 12)
    {
        printf("Good job! You answered most sentences correctly \n");
    }
    else if (score >= 1)
    {
        printf("Keep practicing sentence completion \n");
    }
    else
    {
        printf("Try again and practice more \n\n BEST OF LUCK \n");
    }
    printf("\n IMPORTANT MESSAGE \n\n  This game is for awareness and learning purposes only \n\n");
    printf("\nAGAIN \n\n It cannot diagnose Developmental Language Disorder \n\n");
    return;
}
void case4_game1_run(void) {
    char positive[8][20] = {"flower", "butterfly", "tourist", "puppy","garden", "visa", "table", "pluto"};
    char negative[8][20] = { "knife", "fire", "accident", "terror","injury", "virus", "attack", "earthquake"};
    int i;
    int leftType;
    int question;
    int correct;
    int key;
    int wordType;
    char *leftWord;
    char *rightWord;
    char *questionWord;
    double start, end, reaction;
    double positiveTime = 0;
    double negativeTime = 0;
    int positiveCorrect = 0;
    int negativeCorrect = 0;
    srand(time(0));
    printf("========================================\n");
    printf("             DOT-PROBE TASK\n");
    printf("========================================\n\n");
    printf("So two words will be appearing on the screen.\n");
    printf("You have to remember their positions well.\n\n");
    printf("After the words disappear:\n");
    printf("LEFT ARROW  = word was on the LEFT\n");
    printf("RIGHT ARROW = word was on the RIGHT\n\n");
    printf("Answer as quickly and accurately as possible.\n\n");
    printf("So champ! press any key to start buddy!...");
    getch();
    system("cls");
    for(i = 1; i <= 20; i++)
    {
        printf("\n\n");
        printf("          GET READY FOR ROUND %d\n\n", i);
        Sleep(1000);
        system("cls");
        printf("                    3\n");
        Sleep(1000);
        system("cls");
        printf("\n\n");
        printf("                    2\n");
        Sleep(1000);
        system("cls");
        printf("\n\n");
        printf("                    1\n");
        Sleep(1000);
        system("cls");
        printf("\n\n");
        printf("                  READY!\n");
        Sleep(500);
        system("cls");
        leftType = rand() % 2;
        if(leftType == 0)
        {
            leftWord = positive[rand() % 8];
            rightWord = negative[rand() % 8];
        }
        else
        {
            leftWord = negative[rand() % 8];
            rightWord = positive[rand() % 8];
        }
        question = rand() % 2;
        if(question == 0)
        {
            questionWord = leftWord;
            correct = 75;        
            if(leftType == 0)
            {
                wordType = 1;   
            }
            else
            {
                wordType = 2;  
            }
        }
        else
        {
            questionWord = rightWord;
            correct = 77;       
            if(leftType == 0)
            {
                wordType = 2;   
            }
            else
            {
                wordType = 1;   
            }
        }
        printf("\n\n");
        printf("              ROUND %d / 20\n\n", i);
        printf("           %-15s %s\n", leftWord, rightWord);
        Sleep(500);
        system("cls");
        printf("\n\n");
        printf("              ROUND %d / 20\n\n", i);
        printf("       Where was \"%s\"?\n\n", questionWord);
        printf("          <- LEFT       RIGHT ->\n");
        start = (double)clock() / CLOCKS_PER_SEC;
        key = getch();
        if(key == 0 || key == 224)
        {
            key = getch();
        }
        end = (double)clock() / CLOCKS_PER_SEC;
        reaction = (end - start) * 1000;
        if(key == correct)
        {
            printf("\nCorrect!\n");
            if(wordType == 1)
            {
                positiveTime = positiveTime + reaction;
                positiveCorrect++;
            }
            else if(wordType == 2)
            {
                negativeTime = negativeTime + reaction;
                negativeCorrect++;
            }
        }
        else
        {
            printf("\nWrong!\n");
        }
        printf("Reaction Time: %.0f ms\n", reaction);
        Sleep(700);
        system("cls");
    }
    printf("========================================\n");
    printf("             FINAL RESULTS\n");
    printf("========================================\n\n");
    if(positiveCorrect > 0)
    {
        printf("Positive Words\n");
        printf("Correct Answers: %d\n", positiveCorrect);
        printf("Average Reaction Time: %.2f ms\n\n",
               positiveTime / positiveCorrect);
    }
    else
    {
        printf("No correct responses for positive words.\n\n");
    }
    if(negativeCorrect > 0)
    {
        printf("Negative / Threat Words\n");
        printf("Correct Answers: %d\n", negativeCorrect);
        printf("Average Reaction Time: %.2f ms\n\n",
               negativeTime / negativeCorrect);
    }
    else
    {
        printf("No correct responses for negative words.\n\n");
    }
    if(positiveCorrect > 0 && negativeCorrect > 0)
    {
        printf("----------------------------------------\n");
        if((negativeTime / negativeCorrect) < (positiveTime / positiveCorrect))  
        {
            printf("You should consider visiting a Psychologist my friend! \n");
        }
        else if((positiveTime / positiveCorrect) <= (negativeTime / negativeCorrect))            
        {
            printf("You are just posatively fine my friend!\n");
        }
        printf("----------------------------------------\n");
    }
    printf("\nNote: This task is only a research\n");
    printf("observation and cannot diagnose GAD.\n");
    printf("\nPress any key to exit...");
    getch();
    return;
}
void case4_game2_run(void)
{
    int i;
    int wordType;
    int wordNumber;
    int colour;
    int answer;
    int positiveCorrect = 0;
    int negativeCorrect = 0;
    double startTime;
    double endTime;
    double reactionTime;
    double positiveTime = 0;
    double negativeTime = 0;
    char positive[8][20] = {
        "flower", "puppy", "garden", "butterfly",
        "holiday", "friend", "smile", "sunshine"
    };

    char negative[8][20] = {
        "knife", "fire", "accident", "attack",
        "injury", "terror", "virus", "earthquake"
    };
    srand((unsigned int)time(0));
    printf("============================================\n");
    printf("           COLOUR WORD QUIZ\n");
    printf("============================================\n\n");
    printf("In this game, a word will appear in a colour.\n");
    printf("Ignore the meaning of the word.\n");
    printf("Identify the COLOUR as quickly as possible.\n\n");
    printf("1 = RED, 2 = GREEN, 3 = BLUE, 4 = YELLOW\n\n");
    printf("Press any key to start...");
    getch();
    for(i = 1; i <= 20; i++)
    {
        wordType = rand() % 2;
        wordNumber = rand() % 8;
        colour = rand() % 4 + 1;
        system("cls");
        printf("\n\n");
        printf("             ROUND %d / 20\n\n", i);
        Sleep(2000);
        system("cls");
        printf("1 = RED, 2 = GREEN, 3 = BLUE, 4 = YELLOW\n");
        Sleep(3000);
        system("cls");
        printf("             GET READY...\n");
        Sleep(1000);
        system("cls");
        printf("\n\n");
        printf("                  3");
        Sleep(700);
        system("cls");
        printf("\n\n");
        printf("                  2");
        Sleep(700);
        system("cls");
        printf("\n\n");
        printf("                  1");
        Sleep(700);
        system("cls");
        if(wordType == 0)
        {
            printf("\n\n");
            printf("                 %s\n", positive[wordNumber]);
        }
        else
        {
            printf("\n\n");
            printf("                 %s\n", negative[wordNumber]);
        }
        if(colour == 1)
        {
            system("color 0C");
        }
        else if(colour == 2)
        {
            system("color 0A");
        }
        else if(colour == 3)
        {
            system("color 09");
        }
        else
        {
            system("color 0E");
        }
        startTime = clock();
        answer = getch();
        endTime = clock();
        reactionTime = (endTime - startTime) / CLOCKS_PER_SEC;
        system("color 07");
        system("cls");

        if(answer == '1')
        {
            if(colour == 1)
                printf("\nCorrect!");
            else
                printf("\nWrong!");
        }
        else if(answer == '2')
        {
            if(colour == 2)
                printf("\nCorrect!");
            else
                printf("\nWrong!");
        }
        else if(answer == '3')
        {
            if(colour == 3)
                printf("\nCorrect!");
            else
                printf("\nWrong!");
        }
        else if(answer == '4')
        {
            if(colour == 4)
                printf("\nCorrect!");
            else
                printf("\nWrong!");
        }
        else
        {
            printf("\nInvalid key!");
        }
        printf("\nReaction Time: %.2f seconds", reactionTime);
        if(wordType == 0)
        {
            if(answer == '1' && colour == 1)
            {
                positiveCorrect++;
                positiveTime += reactionTime;
            }
            else if(answer == '2' && colour == 2)
            {
                positiveCorrect++;
                positiveTime += reactionTime;
            }
            else if(answer == '3' && colour == 3)
            {
                positiveCorrect++;
                positiveTime += reactionTime;
            }
            else if(answer == '4' && colour == 4)
            {
                positiveCorrect++;
                positiveTime += reactionTime;
            }
        }
        else
        {
            if(answer == '1' && colour == 1)
            {
                negativeCorrect++;
                negativeTime += reactionTime;
            }
            else if(answer == '2' && colour == 2)
            {
                negativeCorrect++;
                negativeTime += reactionTime;
            }
            else if(answer == '3' && colour == 3)
            {
                negativeCorrect++;
                negativeTime += reactionTime;
            }
            else if(answer == '4' && colour == 4)
            {
                negativeCorrect++;
                negativeTime += reactionTime;
            }
        }
        Sleep(1000);
    }
    system("cls");
    printf("============================================\n");
    printf("              FINAL RESULTS\n");
    printf("============================================\n\n");
    printf("Positive/Neutral Words\n");
    printf("----------------------\n");
    printf("Correct Answers: %d\n", positiveCorrect);
    if(positiveCorrect > 0)
    {
        printf("Average Reaction Time: %.2f seconds\n",
               positiveTime / positiveCorrect);
    }
    else
    {
        printf("Average Reaction Time: No data\n");
    }
    printf("\nThreat-related Words\n");
    printf("--------------------\n");
    printf("Correct Answers: %d\n", negativeCorrect);
    if(negativeCorrect > 0)
    {
        printf("Average Reaction Time: %.2f seconds\n",
               negativeTime / negativeCorrect);
    }
    else
    {
        printf("Average Reaction Time: No data\n");
    }
    printf("\n============================================\n");
    printf("              OBSERVATION\n");
    printf("============================================\n\n");
    if(positiveCorrect > 0 && negativeCorrect > 0)
    {
        if((negativeTime / negativeCorrect) <
           (positiveTime / positiveCorrect))
        {
            printf("Faster average responses were observed\n");
            printf("during threat-related word trials.\n");
        }
        else if((negativeTime / negativeCorrect) >
                (positiveTime / positiveCorrect))
        {
            printf("Slower average responses were observed\n");
            printf("during threat-related word trials.\n");
        }
        else
        {
            printf("The average reaction times were similar.\n");
        }
    }
    else
    {
        printf("Not enough correct responses to compare\n");
        printf("the two groups.\n");
    }
    printf("\nNOTE:\n");
    printf("This is an educational demonstration of\n");
    printf("attention and reaction time.\n");
    printf("It cannot diagnose Generalized Anxiety Disorder.\n");
    printf("\nPress any key to exit...");
    getch();
}
void case5_game1_run(void) {
    char answer[20];
    int choice, score;
    clock_t start, end;
    double reactionTime;
    printf("===== LETTER SWAP GAME =====\n\n");
    printf("Choose a word:\n");
    printf("1. CAT\n");
    printf("2. DOG\n");
    printf("3. BAT\n");
    printf("4. TOP\n");
    printf("5. RAM\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("\nCAT -> ");
        start = clock();
        scanf("%s", answer);
        end = clock();
        reactionTime = (double)(end - start) / CLOCKS_PER_SEC;
        if (strcmp(answer, "ACT") == 0)
        {
            if (reactionTime < 5.0)
                score = 100;
            else
                score = 50;

            printf("Correct!\n");
            printf("Reaction Time = %.2f seconds\n", reactionTime);
            printf("Score = %d\n", score);
        }
        else
        {
            if (reactionTime < 5.0)
                score = 20;
            else
                score = 0;

            printf("Wrong answer!\n");
            printf("Score = %d\n", score);
        }
    }
    else if (choice == 2)
    {
        printf("\nDOG -> ");
        start = clock();
        scanf("%s", answer);
        end = clock();
        reactionTime = (double)(end - start) / CLOCKS_PER_SEC;
        if (strcmp(answer, "GOD") == 0)
        {
            if (reactionTime < 5.0)
                score = 100;
             else
                score = 50;

            printf("Correct!\n");
            printf("Reaction Time = %.2f seconds\n", reactionTime);
            printf("Score = %d\n", score);
        }
        else
        {
            if (reactionTime < 5.0)
                score = 20;
             else
                score = 0;

            printf("Wrong answer!\n");
            printf("Score = %d\n", score);
        }
    }  
else if (choice == 3)
    {
        printf("\nBAT -> ");
        start = clock();
        scanf("%s", answer);
        end = clock();
        reactionTime = (double)(end - start) / CLOCKS_PER_SEC;
        if (strcmp(answer, "TAB") == 0)
        {
            if (reactionTime < 5.0)
                score = 100;
            else
                score = 50;
            printf("Correct!\n");
            printf("Reaction Time = %.2f seconds\n", reactionTime);
            printf("Score = %d\n", score);
        }
        else
        {
            if (reactionTime < 5.0)
                score = 20;
            else
                score = 0;

            printf("Wrong answer!\n");
            printf("Score = %d\n", score);
        }
    }
    else if (choice == 4)
    {
        printf("\nTOP -> ");
        start = clock();
        scanf("%s", answer);
        end = clock();
        reactionTime = (double)(end - start) / CLOCKS_PER_SEC;
        if (strcmp(answer, "POT") == 0)
        {
            if (reactionTime < 5.0)
                score = 100;
             else
                score = 50;
            printf("Correct!\n");
            printf("Correct!\n");
            printf("Reaction Time = %.2f seconds\n", reactionTime);
            printf("Score = %d\n", score);
        }
        else
        {
            if (reactionTime < 5.0)
                score = 20;
             else
                score = 0;
            printf("Wrong answer!\n");
            printf("Score = %d\n", score);
        }
    }
else if (choice == 5)
    {
        printf("\nRAM -> ");
        start = clock();
       scanf("%s", answer);
       end = clock();
      reactionTime = (double)(end - start)/ CLOCKS_PER_SEC;
        if (strcmp(answer, "ARM") == 0)
        {
            if (reactionTime < 5.0)
                score = 100;
             else
                score = 50;
            printf("Correct!\n");
            printf("Reaction Time = %.2f seconds\n", reactionTime);
            printf("Score = %d\n", score);
        }
        else
        {
            if (reactionTime < 5.0)
                score = 20;
             else
                score = 0;
            printf("Wrong answer!\n");
            printf("Score = %d\n", score);
        }
    }
    else
    {
        printf("Invalid choice!\n");
    }
    return;
}
void case5_game2_run(void) {
    char answer[20];
    clock_t start, end;
    double reactionTime;
    int score;
    int choice;
    int round;
    int totalScore = 0;
    printf("===== RHYMING WORD GAME =====\n");
    for (round = 1; round <= 5; round++)
    {
        printf("\n===== ROUND %d =====\n", round);
        printf("Choose a word:\n");
        printf("1. CAT\n");
        printf("2. DOG\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("\nWord: CAT\n");
            printf("Type a rhyming word: ");

            start = clock();
            scanf("%s", answer);
            end = clock();
            reactionTime = (double)(end - start) / CLOCKS_PER_SEC;
            if (strcmp(answer, "hat") == 0 ||
                strcmp(answer, "rat") == 0 ||
                strcmp(answer, "fat") == 0 ||
                strcmp(answer, "mat") == 0 ||
                strcmp(answer, "bat") == 0)
            {
                if (reactionTime < 5.0)
                    score = 100;
                else
                    score = 50;

                printf("Correct!\n");
            }
            else
            {
                score = 0;
                printf("Wrong answer!\n");
            }
        }
        else if (choice == 2)
        {
            printf("\nWord: DOG\n");
            printf("Type a rhyming word: ");

            start = clock();
            scanf("%s", answer);
            end = clock();
            reactionTime = (double)(end - start) / CLOCKS_PER_SEC;
            if (strcmp(answer, "log") == 0 ||
                strcmp(answer, "fog") == 0 ||
                strcmp(answer, "frog") == 0)
            {
                if (reactionTime < 5.0)
                    score = 100;
                else
                    score = 50;

                printf("Correct!\n");
            }
            else
            {
                score = 0;
                printf("Wrong answer!\n");
            }
        }
        else
        {
            score = 0;
            reactionTime = 0;
            printf("Invalid choice!\n");
        }
        printf("Reaction Time = %.2f seconds\n", reactionTime);
        printf("Round Score = %d\n", score);
        totalScore = totalScore + score;
    }
    printf("\n===== GAME OVER =====\n");
    printf("Total Score = %d / 500\n", totalScore);
    return;
}
int main(void) {
    int choice;
    do{
    	system("cls");
        printf("\n=========================================\n");
        printf("             Team Beta!\n");
        printf("=========================================\n");
        printf(" press 1 for Major Depressive Disorder\n");
        printf(" press 2 for Stroke-Related Cognitive Impairment\n");
        printf(" press 3 for Developmental Language Disorder\n");
        printf(" press 4 for Generalized Anxiety Disorder :Threat Bias & Hypervigilance\n");
        printf(" press 5 for Dyslexia\n");
        printf(" press 0 to exit\n");
        printf("=========================================\n");
        printf("Enter your choice buddy!:\n ");
        scanf("%d", &choice);
        Sleep(1000);
        system("cls");
        switch (choice) {
            case 1:
            	printf("1st game\n");
            	Sleep(1000);
                system("cls");
                case1_game1_run();
                Sleep(1000);
                system("cls");
                printf("2nd game\n");
            	Sleep(1000);
                system("cls");
                case1_game2_run();
                break;
            case 2:
            	printf("1st game\n");
            	Sleep(1000);
                system("cls");
                case2_game1_run();
                Sleep(1000);
                system("cls");
                printf("2nd game\n");
            	Sleep(1000);
                system("cls");
                case2_game2_run();
                break;
            case 3:
            	printf("1st game\n");
            	Sleep(1000);
                system("cls");
                case3_game1_run();
                Sleep(1000);
                system("cls");
                printf("2nd game\n");
            	Sleep(1000);
                system("cls");
                case3_game2_run();
                break;
            case 4:
            	printf("1st game\n");
            	Sleep(1000);
                system("cls");
                case4_game1_run();
                Sleep(1000);
                system("cls");
                printf("2nd game\n");
            	Sleep(1000);
                system("cls");
                case4_game2_run();
                break;
            case 5:
            	printf("1st game\n");
            	Sleep(1000);
                system("cls");
                case5_game1_run();
                Sleep(1000);
                system("cls");
                printf("2nd game\n");
            	Sleep(1000);
                system("cls");
                case5_game2_run();
                break;
            case 0:
                printf("\nExiting Goodbye! have a nice day buddy\n");
                break;
            default:
                printf("\nInvalid choice! Please try again buddy.\n");
            }
        }while(choice!=0);
    return 0;
}
