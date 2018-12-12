#include "encrypt.h"


encrypt::encrypt()
{

}

void encrypt::encryption(QString filename)
{
    //Start a timer to be used for random math
    //Start clock_t here, then send it to whatever function is going to handle the math
    //That function will calculate duration and send it back to be used here or by a different function
    //When done... add a delay immediately after starting the timer for X amount of time (random #) before continuing the program
    clock_t start;
    double delay, duration = 0, thousand = 1000.0;
    start = clock();
    delay = randomNum();//add delay of 1-3 seconds using double w/ precision of 1. (1.0, 1.1, 1.2, ..., 2.9, 3.0)
    duration = delay * thousand;
    DWORD dur = static_cast<DWORD>(duration);

    //call function to delay by amount held by the delay variable
    Sleep(dur);


    //TODO: readin keyboard.txt 1 character at a time into a vector until empty
    //when done doing that below... instead make a function that does everything below.
    //the function fills a public vector variable called "keyboardVec" with everything in keyboard.txt.

    QString path = QDir::currentPath();
    path.append("/keyboard.txt");
    QFile keyboardFile(path);
    //QFile keyboardFile("keyboard.txt");
    QTextStream keyboardStream(&keyboardFile);
    QString line;
    //qDebug() << keyboardFile;

    if(keyboardFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //qDebug() << "I GOT HERE!!!!!" << endl;
        do
        {
            line = keyboardStream.read(1);
            if (line == " ")
            {
                addToKeyVec(line);
                continue;
            }
            addToKeyVec(line);

        }while(!line.isNull());

        keyboardFile.flush();
        keyboardFile.close();
    }
    QVector<QString> testing = getit();
    qDebug() << "length of keyboard is: " << testing.length() << endl;
    qDebug() << "size of keyboard is: " << testing.size() << endl;
    for (int i = 0; i < testing.size(); i++)//length is counting end of file as character, so need to subtract 1 from size
    {
        line += getIndex(i);
        qDebug() << i << "." << getIndex(i) << endl;
    }
    //qDebug() << line << endl;
    qDebug() << "size of keyboard is: " << testing.size() << endl;


    /*
     * END OF STEP 1
     * START OF STEP 2
     */

    generateKey(start);

    QString lef, rit;
    testing = left_getit();
    qDebug() << "left size is: " << testing.size() << endl;
    for (int i = 0; i < testing.size()-1; i++)//length is counting end of file as character, so need to subtract 1 from size
    {
        lef += getLeftIndex(i);
        //qDebug() << line;
    }
    qDebug() << "left vector encrypt is: " << lef << endl;

    testing = right_getit();
    qDebug() << "right size is: " << testing.size() << endl;
    for (int i = 0; i < testing.size()-1; i++)//length is counting end of file as character, so need to subtract 1 from size
    {
        rit += getRightIndex(i);
        //qDebug() << line;
    }
    qDebug() << "right vector encrypt is: " << rit << endl;


    /*
     * END OF STEP 2
     * START OF STEP 3
     */

    //Open .txt, .doc, or .docx file to be encrypted
    QFile file(filename); //open user defined file
    QTextStream stream(&file); //set up a filestream to read-in from file
    //QString line; //can use line to hold 1 character at a time
    QString enc_string; //add each character from line to hold the entire encrypted text to later stream back into the file
    //encrypt character; //used to call encrypt class functions such as character.encryption(line)
    line = "";



    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        do
        {
            line = stream.read(1);
            qDebug() << "line character is: " << line << endl;
            for (int i = 0; i < testing.size()-1; i++)
            {
                if(line == "")
                    break;
                if(line == getLeftIndex(i))
                {
                    //line = getRightIndex(i);
                    //enc_string = enc_string + line;
                    enc_string += getRightIndex(i);
                    break;
                }
            }
            //enc_string = enc_string + line;
            qDebug() << enc_string << endl;
        }while(!line.isNull());
        //when this is done... repeat the if, do, and while above but do it for write instead of read and just dump all of this with a stream into the same file used for input... overwrite it.



        //qDebug() << enc_string;

        file.flush();
        file.close();
    }



    QVector<int> decrypt_test = decrypt_getit();
    QVector<QString> shifted_nums = shifted_getit();
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        //do a for loop for all the numbers to calculate with for decrypt... then stream enc_string last
        for(int i = 0; i < decrypt_test.size(); i++)//changed from decrypt_test.size()-1
        {
            //cout << decrypt_test.at(i) << endl;
            stream << decrypt_test.at(i) << "\n";
            stream << shifted_nums.at(i) << "\n";

        }
        stream << enc_string;


        file.flush();
        file.close();
    }
    decrypt_test.clear();
    shifted_nums.clear();
    testing = getit();
    testing.clear();
    testing = left_getit();
    testing.clear();
    testing = right_getit();
    testing.clear();




}

void encrypt::decryption(QString filename)
{
    QString path = QDir::currentPath();
    path.append("/keyboard.txt");
    QFile keyboardFile(path);
    //QFile keyboardFile("keyboard.txt");
    QTextStream keyboardStream(&keyboardFile);
    QString line;
    //qDebug() << keyboardFile;

    if(keyboardFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //qDebug() << "I GOT HERE!!!!!" << endl;
        do
        {
            line = keyboardStream.read(1);
            if (line == " ")
            {
                addToKeyVec(line);
                continue;
            }
            addToKeyVec(line);

        }while(!line.isNull());

        keyboardFile.flush();
        keyboardFile.close();
    }
    QVector<QString> testing = getit();
    //qDebug() << testing.length() << endl;
    for (int i = 0; i < testing.size(); i++)//length is counting end of file as character, so need to subtract 1 from size
    {
        line += getIndex(i);
        //qDebug() << line;
    }
    //qDebug() << line << endl;
    //qDebug() << testing.size();


    /*
     * END OF STEP 1
     * START OF STEP 2
     */

    //START OF CHANGING THIS COPY PASTE INTO READING IN ALL NUMBERS TO DECRYPT_VEC
    //do this in 2 sets... #1: read in all 190 nums... #2: open to (write?) and delete 190 lines
    //Open .txt, .doc, or .docx file to be encrypted
    QFile file(filename); //open user defined file
    QTextStream stream(&file); //set up a filestream to read-in from file
    //QString line; //can use line to hold 1 character at a time
    QString enc_string, previous, next; //add each character from line to hold the entire encrypted text to later stream back into the file
    //encrypt character; //used to call encrypt class functions such as character.encryption(line)
    line = "";
    int temp_nums;
    QVector<int> decrypt_test;
    QRegExp re("\\d*");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

            do{
                previous = line;
                line = stream.readLine();//first readLine is the _index used
                qDebug() << line << endl;
                if(line.isNull())
                    break;
                if(re.exactMatch(line))
                {
                    next = stream.readLine();
                }
                else{
                    break;
                }

                temp_nums = line.toInt();
                addToDecryptVec(temp_nums);
                if(next.isNull())
                    break;
                if(re.exactMatch(next) || next.contains(" "))
                {
                    line = next;
                }
                else{
                    line = next;
                    break;
                }
                addToShiftedtVec(line);



            } while(!line.isNull());

            qDebug() << "previous is: " << previous << endl;
            qDebug() << "line is: " << line << endl;//line currently holds entire encrypted message w/o nums



        file.flush();
        file.close();
    }


    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        stream << line << "\n";
        previous = stream.readAll();
        //stream << line;//haven't verified this works yet
        stream << previous;

        file.flush();
        file.close();
    }

    //END OF CHANGING THIS COPY PASTE INTO READING IN ALL NUMBERS TO DECRYPT_VEC






    clock_t start;
    start = 0;
    qDebug() << "STARTING GENKEY" << endl;
    generateKey(start);//need to accomodate changes to work for enc and dec







    QString lef, rit;
    testing = left_getit();
    qDebug() << "left size is: " << testing.size() << endl;
    for (int i = 0; i < testing.size()-1; i++)//length is counting end of file as character, so need to subtract 1 from size
    {
        lef += getLeftIndex(i);
        //qDebug() << line;
    }
    qDebug() << "left vector encrypt is: " << lef << endl;

    testing = right_getit();
    qDebug() << "right size is: " << testing.size() << endl;
    for (int i = 0; i < testing.size()-1; i++)//length is counting end of file as character, so need to subtract 1 from size
    {
        rit += getRightIndex(i);
        //qDebug() << line;
    }
    qDebug() << "right vector encrypt is: " << rit << endl;

















    enc_string = "";
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        do
        {
            line = stream.read(1);
            for (int i = 0; i < testing.size()-1; i++)//length is counting end of file as character, so need to subtract 1 from size
            {
                if(line == "")
                    break;
                if(line == getRightIndex(i))
                {
                    //line = getRightIndex(i);
                    //enc_string = enc_string + line;
                    enc_string += getLeftIndex(i);
                    break;
                }
            }
            //enc_string = enc_string + line;
            //qDebug() << enc_string << endl;
        }while(!line.isNull());
        //when this is done... repeat the if, do, and while above but do it for write instead of read and just dump all of this with a stream into the same file used for input... overwrite it.



        //qDebug() << enc_string;

        file.flush();
        file.close();
    }

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        stream << enc_string;

        file.flush();
        file.close();
    }

    testing = getit();
    testing.clear();
    testing = left_getit();
    testing.clear();
    testing = right_getit();
    testing.clear();
    testing = shifted_getit();
    testing.clear();
    decrypt_test = decrypt_getit();
    decrypt_test.clear();

}



double encrypt::randomNum()
{
    double delay, constant = 5.0;
    srand( unsigned(time(nullptr)));
    delay = static_cast<double>(rand())/(RAND_MAX + 1)+1+(rand()%77);
    if (delay > 5)
    {
        delay = fmod(delay, constant);
    }

    return delay;
}

void encrypt::generateKey(clock_t start)
{
    int _index = 0, leftTester, lSize = 0, rSize = 0, temp,
            decrypt_counter = 0, shifted_save = 0, ind_of = 0;
    //int randNum_counter = 0;
    double var = 0.0;
    double duration = 0.0;
    QVector<QString> keyboardVec = getit();
    QVector<QString> leftVec = left_getit();
    QVector<QString> rightVec = right_getit();
    QVector<int> decrypt_press = decrypt_getit();
    QVector<int> shiftedNumVector;
    QVector<int> unshiftedUsableNums;
    QString character, decrypt_nums, shifted_str, shifted_line = "";
    //srand( unsigned(time(nullptr)));//add back in later to see if necessary... already did this in randomNum()
    do
    {
        qDebug() << "lSize top of do is: " << lSize << endl;
        qDebug() << "rSize top of do is: " << rSize << endl;
        //if(lSize >= 94 && rSize >= 94)
        //if(lSize > 94 || rSize > 94)
        //{
            //cout << "lSize is: " << lSize << endl;
            //cout << "rSize is: " << rSize << endl;
            //qDebug() << "running the do while break" << endl;
            //break;//this code should never run due to an update I made
        //}
        if(start != 0)//for encryption button press
        {
            duration = (clock() - start) / static_cast<double>(CLOCKS_PER_SEC);
            var = (var + (duration * static_cast<double>(rand() % 2000 + 1)));
            _index = static_cast<int>(var);
            addToDecryptVec(_index);//a list of numbers for the decrypt
        }
        if(start == 0)//for decryption button press
        {
            if(decrypt_counter == decrypt_press.size())
                break;
            _index = getDecryptIndex(decrypt_counter);//shouldn't go out of bounds but not tested
            shifted_line = getShiftedIndex(decrypt_counter);
            decrypt_counter = decrypt_counter + 1;
            //qDebug() << "_index is: " << _index << endl;
        }
        while(_index > 94)//find a way to use random numbers again without breaking code!!!!
        {
            if(start != 0)
            {
                //_index = _index / 3;
                temp = rand() % 20 + 3;
                shifted_save = temp << 5;
                shifted_str = shifted_str + QString::number(shifted_save) + " ";
                _index = _index / temp;
            }
            if(start == 0)
            {
                while((ind_of = shifted_line.indexOf(" ", ind_of)) != -1)
                {
                    //qDebug() << "Found " " at: " << ind_of << endl;
                    shiftedNumVector.push_back(ind_of);
                    ++ind_of;
                }




                int previous_ind_of = 0, current_ind_of = 0, temporary = 0;
                for(int m = 0; m < shiftedNumVector.size(); m++)//no out of bounds i think????
                {

                    current_ind_of = shiftedNumVector.at(m);
                    int current_length = current_ind_of - previous_ind_of;

                    QString _current = shifted_line.mid(previous_ind_of, current_length);
                    //qDebug() << "_current is: " << _current << endl;

                    //convert string to num, shift num 5 times, run _index = _index / shifted num
                    temporary = _current.toInt();

                    temporary = temporary >> 5;
                    //qDebug() << "_index is: " << _index << endl;
                    //qDebug() << "temporary is: " << temporary << endl;

                    _index = _index / temporary;

                    previous_ind_of = current_ind_of;
                    //qDebug() << "_index is: " << _index << endl;
                }
                //_index = _index / 17;//FOR TESTING PURPOSES ONLY... REMOVE LATER
                shifted_line = "";
                ind_of = 0;
                //randNum_counter = 0;
                shiftedNumVector.clear();

            }

        }//idea... take random number, bitshift right 5 times,
        //save as string of numbers until while finishes
        //then add that string to a vector (yes im adding a 5th vector to this project)
        //they will be added to the project just like the previous numbers...
        //so now lines 1-2 coordinate, lines 3-4 coordinate, so on so forth....
        //ex: line1: 400
        //    line2: 4 21
        //    line3: 627
        //    line4: 3 9
        //    etc etc......

        //cout << "Index is: " << _index << endl;
        if(start != 0)
        {
            addToShiftedtVec(shifted_str);
            shifted_str = "";
        }

        leftVec = left_getit();
        rightVec = right_getit();
        //cout << "left size: " << leftVec.size() << endl;;
        //cout << "right size: " << rightVec.size() << endl;
        character = getIndex(_index);

        if(leftVec.size() == 0)
        {
            addToLeftVec(character);
            lSize = leftVec.size();
            continue;
        }

        leftTester = leftVec.size();
        for(int i = 0; i < leftVec.size(); i++)
        {
            if(character == getLeftIndex(i))
            {
                break;
            }
            if(i == leftVec.size()-1 && character != getLeftIndex(i))
            {
                addToLeftVec(character);
                leftVec = left_getit();
                lSize = leftVec.size();
                //cout << lSize << endl;
                //cout << rSize << endl;
                break;
            }
        }

        if(leftTester < leftVec.size())
        {
            //cout << "in tester" << endl;
            continue;
        }

        if(rightVec.size() == 0)
        {
            addToRightVec(character);
            rSize = rightVec.size();
            continue;
        }
        for(int j = 0; j < rightVec.size(); j++)
        {
            if(character == getRightIndex(j))
            {
                //call function 2.5 since  both leftVec and rightVec contain the character already
                //cout << "calling generateKeyHelper()" << endl;
                generateKeyHelper(keyboardVec, leftVec, rightVec, _index);
                leftVec = left_getit();
                rightVec = right_getit();
                lSize = leftVec.size();
                rSize = rightVec.size();
                //cout << "generateKeyHelper finished!!" << endl;
                break;
            }
            if(j == rightVec.size()-1 && character != getLeftIndex(j))
            {
                addToRightVec(character);
                rightVec = right_getit();
                rSize = rightVec.size();
                //cout << "-------coming from the right side-------" << endl;
                //cout << lSize << endl;
                //cout << rSize << endl;
                //cout << "-------ending from the right side-------" << endl;
                break;
            }
        }
        leftVec = left_getit();
        rightVec = right_getit();
        lSize = leftVec.size();
        rSize = rightVec.size();
        //qDebug() << "left size: " << leftVec.size() << endl;;
        //qDebug() << "right size: " << rightVec.size() << endl;
    }while(lSize != 97 || rSize != 97);//doesn't break if 95... trying 97

    //while (lSize <= 94 && rSize < 94);
    qDebug() << "we are outside the do while!" << endl;
    leftVec = left_getit();
    rightVec = right_getit();
    lSize = leftVec.size();
    rSize = rightVec.size();
    qDebug() << "left size: " << leftVec.size() << endl;;
    qDebug() << "right size: " << rightVec.size() << endl;

}

void encrypt::generateKeyHelper(QVector<QString> keyboardVec, QVector<QString> leftVec,
                       QVector<QString> rightVec, int _index)
{
    int lSize = leftVec.size(), rSize = rightVec.size();
    bool upflag = false, downflag = false;
    QString character;
    for(int counter = 1; leftVec.size() == lSize && rightVec.size() == rSize; counter++)
    {
        //lSize = leftVec.size();//added for testing... use if i also add leftTester
        //rSize = rightVec.size();//added for testing... use if i also add rightTester

        if(upflag == true && downflag == true)//this is bad... can be more efficient
        {
            cout << "generateKeyHelper failed!!!!" << endl;//if only goes off once at end then the run was successful
            break;
        }
        if(upflag == true)//go down 1 at a time until _index - counter < 0
        {
            if(_index < 0)
            {
                downflag = true;
                break;
            }
            character = getIndex(_index);
            for(int i = 0; i < leftVec.size(); i++)
            {
                if(character == getLeftIndex(i))
                    break;
                else if(i == leftVec.size()-1 && character != getLeftIndex(i))
                {
                    addToLeftVec(character);
                    leftVec = left_getit();
                    break;
                }
            }
            if(lSize < leftVec.size())
                break;

            for(int j = 0; j < leftVec.size(); j++)
            {
                if(character == getRightIndex(j))
                    break;
                else if(j == rightVec.size()-1 && character != getRightIndex(j))
                {
                    addToRightVec(character);
                    rightVec = right_getit();
                    break;
                }
            }
            if(rSize < rightVec.size())
                break;
            _index = _index - 1;
            continue;
            //do stuff then "continue;"

        }
        if(downflag == true)//go up 1 at a time until _index + counter < 0
        {
            if(_index > 97)//works at 94... trying 97
                break;
            character = getIndex(_index);
            for(int i = 0; i < leftVec.size(); i++)
            {
                if(character == getLeftIndex(i))
                    break;
                if(i == leftVec.size()-1 && character != getLeftIndex(i))
                {
                    addToLeftVec(character);
                    leftVec = left_getit();
                    break;
                }
            }
            if(lSize < leftVec.size())
                break;

            for(int j = 0; j < leftVec.size(); j++)
            {
                if(character == getRightIndex(j))
                    break;
                else if(j == rightVec.size()-1 && character != getRightIndex(j))
                {
                    addToRightVec(character);
                    rightVec = right_getit();
                    break;
                }
            }
            if(rSize < rightVec.size())
                break;
            _index = _index + 1;
            continue;

            //do stuff then "continue;"
        }

        if(counter % 2 == 1)//go up as long as in range
        {
            if(_index + counter >= 97)//changed to >= from >... change back if this doesn't fix it
            {//worked as 94.... trying it at 97
                upflag = true;
                _index = _index + counter;
                continue;
            }
            character = getIndex(_index);
            for(int i = 0; i < leftVec.size(); i++)
            {
                if(character == getLeftIndex(i))
                    break;
                else if(i == leftVec.size()-1 && character != getLeftIndex(i))
                {
                    addToLeftVec(character);
                    leftVec = left_getit();
                    break;
                }
            }
            if(lSize < leftVec.size())
                break;

            for(int j = 0; j < leftVec.size(); j++)
            {
                if(character == getRightIndex(j))
                    break;
                else if(j == rightVec.size()-1 && character != getRightIndex(j))
                {
                    addToRightVec(character);
                    rightVec = right_getit();
                    break;
                }
            }
            if(rSize < rightVec.size())
                break;



            _index = _index + counter;

        }
        if(counter % 2 == 0)//go down as long as in range
        {
            if(_index - counter <= 0)//changed to >= from >... change back if this doesn't fix it
            {
                downflag = true;
                _index = _index - counter;
                continue;
            }
            character = getIndex(_index);
            for(int i = 0; i < leftVec.size(); i++)
            {
                if(character == getLeftIndex(i))
                    break;
                else if(i == leftVec.size()-1 && character != getLeftIndex(i))
                {
                    addToLeftVec(character);
                    leftVec = left_getit();
                    break;
                }
            }
            if(lSize < leftVec.size())
                break;

            for(int j = 0; j < leftVec.size(); j++)
            {
                if(character == getRightIndex(j))
                    break;
                else if(j == rightVec.size()-1 && character != getRightIndex(j))
                {
                    addToRightVec(character);
                    rightVec = right_getit();
                    break;
                }
            }
            if(rSize < rightVec.size())
                break;
            _index = _index - counter;

        }

    }


}

