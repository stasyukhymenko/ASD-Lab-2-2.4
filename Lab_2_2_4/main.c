#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265358979323846

int n = 12;
double** T;
int GraphType;

double** randm(int n) {

    srand(2328);

    double** arr = malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        arr[i] = malloc(sizeof(double) * n);
        for (int j = 0; j < n; j++) {
            arr[i][j] = (double)rand() / (double)RAND_MAX * 2.0;
        }
    }
    return arr;
}

void deallocateMemory(double** arr, int n) {
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
}

void printArrayWithSpaces(double** arr, int n) {
    printf("\n");
    for (int j = 0; j < n; j++) {
        if (j > 9) {
            printf("  %d ", j + 1);
        }
        else {
            printf("    %d", j + 1);
        }
    }
    printf("\n\n");
    for (int i = 0; i < n; i++) {
        if (i > 8) {
            printf("%d", i + 1);
        }
        else {
            printf(" %d", i + 1);
        }

        for (int j = 0; j < n; j++) {
            printf("  %.0f  ", (double)arr[i][j]);
        }
        printf("\n\n");
    }
    printf("\n\n");
}

void printArrayTabulation(double** arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.0f\t", (double)arr[i][j]);
        }
        printf("\n\n");
    }
    printf("\n\n");
}

void mulmr(double k, double** arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = round(k * arr[i][j]);
        }
    }
}

double** graphUndirected(double** arr, int n) {
    double** undirectedArr = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        undirectedArr[i] = (double*)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            undirectedArr[i][j] = arr[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (undirectedArr[i][j] == 1 && undirectedArr[j][i] == 0) {
                undirectedArr[j][i] = 1;
            }
        }
    }

    return undirectedArr;
}

int** powerDirected(double** array, int n) {
    int pIn = 0;
    int pOut = 0;
    int** homogenAll = malloc(sizeof(int*) * 2);
    for (int i = 0; i < 2; i++) {
        homogenAll[i] = malloc(sizeof(double) * n);
        for (int j = 0; j < n; j++) {
            homogenAll[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (array[i][j] == 1) {
                pOut += 1;
            }
        }
        for (int k = 0; k < n; k++) {
            if (array[k][i] == 1) {
                pIn += 1;
            }
        }
        printf("In power: %d - %d\n", i + 1, pIn);
        homogenAll[0][i] = pIn;
        printf("Out power: %d - %d\n", i + 1, pOut);
        homogenAll[1][i] = pOut;
        pIn = 0;
        pOut = 0;
    }
    return homogenAll;
}

int* powerUndirected(double** array, int n) {
    int P = 0;
    int* homogen = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (array[i][j] == 1) {
                P += 1;
            }
        }
        printf("Power: %d - %d\n", i + 1, P);
        homogen[i] = P;
        P = 0;
    }
    return homogen;
}

void isHomogen(int* array, int n) {
    int pwr = 0;
    pwr = array[0];
    for (int k = 1; k < n; k++) {
        if (array[k] != pwr) {
            printf("Graph is not homogeneous\n");
            return;
        }
    }
    printf("Graph is homogeneous\nPower: %d", pwr);
}

void isIsolated(int* array, int n) {
    int isIsolated = 0;
    for (int i = 0; i < n; i++) {
        if (array[i] == 0) {
            isIsolated++;
            printf("Amount of isolated nodes: %d\n", array[i]);
        }
    }
    printf("Amount of isolated nodes: %d\n", isIsolated);
}

void isHanging(int* array, int n) {
    int isHanging = 0;
    for (int i = 0; i < n; i++) {
        if (array[i] == 1) {
            isHanging++;
            printf("Hanging node = %d\n", array[i]);
        }
    }
    printf("Hanging nodes = %d\n", isHanging);
}

double** multiplyMatrix(double** array, double** array2, int n) {
    double** matrix = malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(sizeof(double) * n);
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++)
            {
                matrix[i][j] += array[i][k] * array2[k][j];
            }
        }

    }
    return matrix;
}

double** addMatrix(double** array, double** array2, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            array[i][j] += array2[i][j];
        }
    }
    return array;
}

void B(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != 0) {
                matrix[i][j] = 1;
            }
        }
    }

}

void clearMatrix(double** matrix, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
}

double** accessebilityMatrix(double** array, int n) {
    double** res = malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        res[i] = malloc(sizeof(double) * n);
        for (int j = 0; j < n; j++) {
            res[i][j] = 0;
        }
    }
    double** temp = malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        temp[i] = malloc(sizeof(double) * n);
        for (int j = 0; j < n; j++) {
            temp[i][j] = 0;
        }
    }
    addMatrix(res, array, n);
    double** mult;
    mult = multiplyMatrix(array, array, n);
    addMatrix(temp, mult, n);
    deallocateMemory(mult, n);
    addMatrix(res, temp, n);
    for (int i = 0; i < n - 3; i++) {
        mult = multiplyMatrix(array, temp, n);
        clearMatrix(temp, n);
        addMatrix(temp, mult, n);
        deallocateMemory(mult, n);
        addMatrix(res, temp, n);
    }
    deallocateMemory(temp, n);
    for (int i = 0; i < n; i++) {
        res[i][i] = res[i][i]++;
    }
    return res;
}

double** transposeMatrix(double** matrix, int n) {
    double** array = malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        array[i] = malloc(sizeof(double) * n);
        for (int j = 0; j < n; j++) {
            array[i][j] = 0;
        }
    }
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            matrix[j][i] = matrix[i][j];
        }
    }
    addMatrix(array, matrix, n);
    return array;
}

double** multiplyMatrixEl(double** matrix1, double** matrix2, int n) {
    double** matrix = malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(sizeof(double) * n);
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = matrix1[i][j] * matrix2[i][j];
        }
    }
    return matrix;
}

double** pathTwo(double** matrixInput, int n) {
    printf("Path with length 2:\n");
    double** matrix = malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(sizeof(double) * n);
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
    addMatrix(matrix, matrixInput, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                for (int k = 0; k < n; k++) {
                    if (matrix[j][k] == 1) {
                        printf("%d --> %d --> %d\n", i + 1, j + 1, k + 1);
                    }
                }
            }
        }
    }
    return matrixInput;
}

double** pathThree(int** matrixInput, int n) {
    printf("Path with length 3:\n");
    double** matrix = malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(sizeof(double) * n);
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
    addMatrix(matrix, matrixInput, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                for (int k = 0; k < n; k++) {
                    if (matrix[j][k] == 1) {
                        for (int m = 0; m < n; m++) {
                            if (matrix[k][m] == 1) {
                                printf("%d --> %d --> %d --> %d\n", i + 1, j + 1, k + 1, m + 1);
                            }
                        }
                    }
                }
            }
        }
    }
    return matrixInput;
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    double c = 1.0 - 2 * 0.01 - 8 * 0.01 - 0.3;

    double** T1;
    double** T2;
    double** T3;
    double** Ta;
    double** Ta2;
    double** S;
    double** N;
    double** TT;
    double** path2;
    double** path3;

    T = randm(n);
    printf("%f", c);
    mulmr(c, T, n);
    wchar_t ProgName[] = L"Lab4, IM-23 Юхименко Станіслав";
    printArrayWithSpaces(T, n);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    HBRUSH hBrush = CreateSolidBrush(RGB(30, 30, 30));
    AllocConsole();
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    while (consoleHandle == INVALID_HANDLE_VALUE)
    {
        Sleep(10);
        consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    FILE* pf;
    freopen_s(&pf, "CONOUT$", "w", stdout);
    printf_s("1) Directed graph;\n");
    printf_s("2) Undirected graph;\n");
    printf_s("Choose type: ");
    freopen_s(&pf, "CONIN$", "r", stdin);
    freopen_s(&pf, "CONOUT$", "w", stdout);
    scanf_s(" %d", &GraphType);

    int* a;
    int* in;
    int** direct;

    if (GraphType == 1)
    {
        printf("Matrix for directed graph:\n\n");
        printArrayWithSpaces(T, n);
        direct = powerDirected(T, n);
        in = direct[0];
        printf("Power: %d\n", in[0]);
        printf("Powers:\n");
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < n; j++) {
                printf("  %d  ", direct[i][j]);
            }
            printf("\n");
        }
       
        isHomogen(in, n);
        isIsolated(in, n);
        isHanging(in, n);

        for (int i = 0; i < 2; i++) {
            free(direct[i]);
        }
        free(direct);
    }
    else if (GraphType == 2)
    {
        graphUndirected(T, n);
        printf("Matrix for undirected graph:\n\n");
        printArrayWithSpaces(T, n);
        a = powerUndirected(T, n);
        isHomogen(a, n);
        isIsolated(a, n);
        isHanging(a, n);
        free(a);
    }
    else {
        printf("Enter 1 or 2 :)");
        Sleep(1500);
        return 0;
    }

    c = 1.0 - 2 * 0.005 - 8 * 0.005 - 0.27;
    printf("T1 matrix:\n");
    T1 = randm(n);
    mulmr(c, T1,n);
    printArrayWithSpaces(T1, n);
    powerDirected(T1, 12);

    printf("T^2 matrix:\n");
    T2 = multiplyMatrix(T1, T1, n);
    printArrayTabulation(T2, n);
    path2 = pathTwo(T1, n);

    T3 = multiplyMatrix(T1, T2, n);
    path3 = pathThree(T1, n);

    printf("T^3 matrix:\n");
    printArrayTabulation(T3, n);

    printf("Matrix of accessebility:\n");
    Ta = accessebilityMatrix(T1, n);
    printArrayTabulation(Ta, n);

    printf("Ta2 matrix:\n");
    Ta2 = multiplyMatrix(Ta, Ta, n);
    printArrayTabulation(Ta2, n);

    printf("Matrix of accessebility:\n");
    B(Ta, n);
    printArrayWithSpaces(Ta, n);

    printf("Transposed matrix:\n");
    TT = transposeMatrix(Ta, n);
    printArrayWithSpaces(TT, n);

    printf("Numered matrix:\n");
    S = multiplyMatrixEl(TT, Ta, n);
    printArrayWithSpaces(S, n);
    printf("Strong connection between all items, so there is no need for rearrangement");

    WNDCLASS w;
    w.lpszClassName = ProgName;
    w.hInstance = hInstance;
    w.lpfnWndProc = WndProc;
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = 0;
    w.lpszMenuName = 0;
    w.hbrBackground = hBrush;
    w.style = CS_VREDRAW;
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;
    if (!RegisterClass(&w))
        return 0;
    HWND hWnd;
    MSG lpMsg;
    hWnd = CreateWindow(ProgName,
        ProgName,
        WS_OVERLAPPEDWINDOW,
        600,
        100,
        1300,
        800,
        (HWND)NULL,
        (HMENU)NULL,
        (HINSTANCE)hInstance,
        (HINSTANCE)NULL);
    ShowWindow(hWnd, nCmdShow);
    while (GetMessage(&lpMsg, hWnd, 0, 0)) {
        TranslateMessage(&lpMsg);
        DispatchMessage(&lpMsg);
    }
  
    deallocateMemory(T, n);
    deallocateMemory(T1, n);
    deallocateMemory(T2, n);
    deallocateMemory(T3, n);
    deallocateMemory(Ta, n);
    deallocateMemory(T2, n);
    deallocateMemory(S, n);
    deallocateMemory(TT, n);
    deallocateMemory(path2, n);
    deallocateMemory(path3, n);

    return(lpMsg.wParam);
}

HDC hdc;
PAINTSTRUCT ps;

void arrow(int x, int y, int x2, int y2)
{
    HPEN ArrowPen = CreatePen(PS_SOLID, 2, RGB(85, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(255, 241, 230));

    SelectObject(hdc, ArrowPen);

    float theta = atan2((int)y2 - (int)y, (int)x2 - (int)x);
    float x_intsct = (int)x2 - (int)16 * cos(theta);
    float y_intsct = (int)y2 - (int)16 * sin(theta);

    int arrowLen = 15;
    int arrowX = x_intsct - arrowLen * cos(theta + PI / 8);
    int arrowY = y_intsct - arrowLen * sin(theta + PI / 8);

    MoveToEx(hdc, x_intsct, y_intsct, NULL);
    LineTo(hdc, arrowX, arrowY);

    arrowX = x_intsct - arrowLen * cos(theta - PI / 8);
    arrowY = y_intsct - arrowLen * sin(theta - PI / 8);

    MoveToEx(hdc, x_intsct, y_intsct, NULL);
    LineTo(hdc, arrowX, arrowY);
    SelectObject(hdc, KPen);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
    switch (messg)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        wchar_t* nn[12] = { L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"10", L"11", L"12" };
        int nx[12];
        int ny[12];
        int x0 = 150;
        int y0 = 600;
        int r = 80;
        int r2 = 120;
        int count = 1;
        int count2 = 1;
        int bY, bX;
        int side = n / 4;
        int dx = 25, dy = 25, dtx = 8;

        HPEN BPen = CreatePen(PS_SOLID, 2, RGB(201, 24, 109));
        HPEN KPen = CreatePen(PS_SOLID, 1, RGB(255, 241, 230));
        HPEN PenThick = CreatePen(PS_SOLID, 1, RGB(255, 241, 230));
        SelectObject(hdc, BPen);

        double fi = 0.0;
        int x = 0, y = 0;

        for (int i = 0; i < n; i++)
        {
            if (i <= side) {
                x = x0;
                y = y0 - r * i * 2;
                bY = y;
            }
            else if (i > side && i <= side * 2) {
                x = x0 + r * count * 2;
                y = bY;
                count++;
                bX = x;
            }
            else if (i > side * 2 && i <= side * 3) {
                count = 1;
                x = bX;
                y = bY + r * count2 * 2;
                count2++;
            }
            else if (i > side * 3 && i <= side * 4) {
                x = bX - r * count * 2;
                y = y0;
                count++;
            }

            if (i == 10 || i == 11) {
                x = (nx[0] + nx[9]) / 2;
                y = (ny[0] + ny[9]) / 2;
                Ellipse(hdc, x - dx, y - dy, x + dx, y + dy);

                x = (nx[0] + nx[9]) / 2;
                y = (ny[1] + ny[2]) / 2;
                Ellipse(hdc, x - dx, y - dy, x + dx, y + dy);
            }

            Ellipse(hdc, x - dx, y - dy, x + dx, y + dy);

            if (i == 10 || i == 11) {
                nx[10] = (nx[0] + nx[9]) / 2;
                ny[10] = ny[0];

                nx[11] = (nx[0] + nx[9]) / 2;
                ny[11] = (ny[1] + ny[2]) / 2;
            }
            nx[i] = x;
            ny[i] = y;
        }
        SelectObject(hdc, KPen);
        int i = 0;
        int oldj = 0;
        int j = 0;

        for (i = 0; i < n; i++)
        {
            oldj++;
            j = oldj;
            for (j; j < n; j++)
            {
                if (T[i][j] == 1)
                {
                    SelectObject(hdc, KPen);
                    float centX = ((int)nx[i] + (int)nx[j]) / 2.0;
                    float centY = ((int)ny[i] + (int)ny[j]) / 2.0;
                    float normalCf = -(nx[j] - nx[i]) / (ny[j] - ny[i] + 0.00001);
                    float vectX = 1.0;
                    float vectY = normalCf;

                    float vectLen = 20.0;
                    float vectNorm = sqrt(vectX * vectX + vectY * vectY);
                    float vectScale = vectLen / vectNorm;

                    vectX *= vectScale;
                    vectY *= vectScale;

                    centX += vectX;
                    centY -= vectY;

                    int newX = (((int)nx[i] + (int)nx[j]) / 2) + 20;
                    int newY = (((int)ny[i] + (int)ny[j]) / 2) + 20;
                    POINT points[] = {
                            {nx[i], ny[i]},
                            {centX, centY},
                            {nx[j], ny[j]},
                    };
                    Polyline(hdc, points, 3);
                    if (GraphType == 1)
                    {
                        arrow(centX, centY, nx[j], ny[j]);
                    }
                }
            }
        }
        oldj = 1;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < oldj; j++)
            {

                if (T[i][j] == 1 && T[j][i] == 0)
                {
                    SelectObject(hdc, KPen);
                    float centX = ((int)nx[i] + (int)nx[j]) / 2.0;
                    float centY = ((int)ny[i] + (int)ny[j]) / 2.0;
                    float normalCf = -(nx[j] - nx[i]) / (ny[j] - ny[i] + 0.00001);
                    float vectX = 1.0;
                    float vectY = normalCf;

                    float vectLen = 20.0;
                    float vectNorm = sqrt(vectX * vectX + vectY * vectY);
                    float vectScale = vectLen / vectNorm;

                    vectX *= vectScale;
                    vectY *= vectScale;

                    centX += vectX;
                    centY -= vectY;

                    int newX = (((int)nx[i] + (int)nx[j]) / 2) + 20;
                    int newY = (((int)ny[i] + (int)ny[j]) / 2) + 20;
                    POINT points[] = {
                            {nx[i], ny[i]},
                            {centX, centY},
                            {nx[j], ny[j]},
                    };
                    Polyline(hdc, points, 3);
                    if (GraphType == 1)
                    {
                        arrow(centX, centY, nx[j], ny[j]);
                    }
                }
                else if (T[i][j] == 1 && T[j][i] == 1 && GraphType == 1 && i != j)
                {
                    SelectObject(hdc, KPen);
                    float centX = ((int)nx[i] + (int)nx[j]) / 2.0;
                    float centY = ((int)ny[i] + (int)ny[j]) / 2.0;
                    float normalCf = -(nx[j] - nx[i]) / (ny[j] - ny[i] + 0.00001);
                    float vectX = 1.0;
                    float vectY = normalCf;

                    float vectLen = 20.0;
                    float vectNorm = sqrt(vectX * vectX + vectY * vectY);
                    float vectScale = vectLen / vectNorm;

                    vectX *= vectScale;
                    vectY *= vectScale;

                    centX += vectX;
                    centY += vectY;

                    int newX = (((int)nx[i] + (int)nx[j]) / 2) + 20;
                    int newY = (((int)ny[i] + (int)ny[j]) / 2) + 20;
                    POINT points[] = {
                            {nx[i], ny[i]},
                            {centX, centY},
                            {nx[j], ny[j]},
                    };
                    Polyline(hdc, points, 3);

                    arrow(centX, centY, nx[j], ny[j]);
                }
            }
            oldj++;
        }
        for (i = 0; i < n; i++)
        {
            if (T[i][i] == 1)
            {
                if (i > 7 && i < 12)
                {
                    Arc(hdc, nx[i] + 25, ny[i] + 50, nx[i] - 25, ny[i], nx[i] - 25, ny[i] + 5, nx[i] + 25, ny[i]);
                    if (GraphType == 1)
                        arrow((nx[i] + 3.5), (ny[i] + 2), nx[i], ny[i]);
                }
                else
                {
                    Arc(hdc, nx[i] - 25, ny[i] - 50, nx[i] + 25, ny[i], nx[i] + 25, ny[i] - 5, nx[i] - 25, ny[i]);
                    if (GraphType == 1)
                        arrow((nx[i] + 3.5), (ny[i] - 2), nx[i], ny[i]);
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            TextOut(hdc, nx[i] - 1, ny[i] - 2, nn[i], 2);
        }
        SelectObject(hdc, BPen);
        Ellipse(hdc, 1000, 350, 1050, 400);
        TextOut(hdc, 1022, 368, TEXT("C"), 1);
        
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
}