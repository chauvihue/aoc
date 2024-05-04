 = 0; j < m; j++) {for (int k = 0; k < 3; k++)
                cout << (dist[i][j][k] == 1e4?".":to_string(dist[i][j][k])) << '|';
                cout << '\t';}
            cout << endl;
            }
            cout << endl;