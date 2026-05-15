#include <iostream>
using namespace std;

struct Card {
    char fruit;
    int cnt;
};

const int MAX = 250000;

Card deckA[MAX], deckB[MAX];
Card center[MAX];

int frontA = 0, backA = 0;
int frontB = 0, backB = 0;
int centerSize = 0;

bool canRing(Card topA, Card topB) {
    int b = 0, c = 0, g = 0, s = 0;

    if (topA.fruit == 'b') b += topA.cnt;
    else if (topA.fruit == 'c') c += topA.cnt;
    else if (topA.fruit == 'g') g += topA.cnt;
    else if (topA.fruit == 's') s += topA.cnt;

    if (topB.fruit == 'b') b += topB.cnt;
    else if (topB.fruit == 'c') c += topB.cnt;
    else if (topB.fruit == 'g') g += topB.cnt;
    else if (topB.fruit == 's') s += topB.cnt;

    return b == 5 || c == 5 || g == 5 || s == 5;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        cin >> fruit >> cnt;
        deckA[backA++] = {fruit, cnt};
    }

    for (int i = 0; i < M; i++) {
        cin >> fruit >> cnt;
        deckB[backB++] = {fruit, cnt};
    }

    Card topA = {0, 0};
    Card topB = {0, 0};

    int turn = 0; // 0: A, 1: B

    for (int move = 0; move < N; move++) {
        if (turn == 0) {
            if (frontA >= backA) break;

            Card cur = deckA[frontA++];
            topA = cur;
            center[centerSize++] = cur;

            if (frontA >= backA) break;

            if (canRing(topA, topB)) {
                for (int i = 0; i < centerSize; i++) {
                    deckA[backA++] = center[i];
                }

                centerSize = 0;
                topA = {0, 0};
                topB = {0, 0};
            }

            turn = 1;
        } else {
            if (frontB >= backB) break;

            Card cur = deckB[frontB++];
            topB = cur;
            center[centerSize++] = cur;

            if (frontB >= backB) break;

            if (canRing(topA, topB)) {
                for (int i = 0; i < centerSize; i++) {
                    deckB[backB++] = center[i];
                }

                centerSize = 0;
                topA = {0, 0};
                topB = {0, 0};
            }

            turn = 0;
        }
    }

    cout << backA - frontA << ' ' << backB - frontB << '\n';

    return 0;
}
