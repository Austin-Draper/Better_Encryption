#ifndef ENCRYPT_H
#define ENCRYPT_H
#include <iostream>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <Windows.h>

using namespace std;
class encrypt
{
private:
    QVector<QString> _keyboardVec;
    QVector<QString> _leftVec;
    QVector<QString> _rightVec;
    QVector<int> _decryptVec;
    QVector<QString> shiftedVec;

public:
    encrypt();
    void encryption(QString);
    void decryption(QString);
    double randomNum();
    void generateKey(clock_t);
    void generateKeyHelper(QVector<QString>, QVector<QString>, QVector<QString>, int);

    const QVector<QString>& getit() const { return _keyboardVec; }
    const QVector<QString>& left_getit() const { return _leftVec; }
    const QVector<QString>& right_getit() const { return _rightVec; }
    const QVector<int>& decrypt_getit() const { return _decryptVec; }
    const QVector<QString>& shifted_getit() const { return shiftedVec; }
    void addToKeyVec(QString x) {_keyboardVec.push_back(x);}
    void addToLeftVec(QString x) {_leftVec.push_back(x);}
    void addToRightVec(QString x) {_rightVec.push_back(x);}
    void addToDecryptVec(int x) {_decryptVec.push_back(x);}
    void addToShiftedtVec(QString x) {shiftedVec.push_back(x);}
    const QString& getIndex(int x) const { return _keyboardVec.at(x);}
    const QString& getLeftIndex(int x) const { return _leftVec.at(x);}
    const QString& getRightIndex(int x) const { return _rightVec.at(x);}
    const int& getDecryptIndex(int x) const { return _decryptVec.at(x);}
    const QString& getShiftedIndex(int x) const { return shiftedVec.at(x);}


};

#endif // ENCRYPT_H
