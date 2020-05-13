//
// Created by Igli milaqi on 12/05/2020.
//

#ifndef CROW_ASSETPARSER_H
#define CROW_ASSETPARSER_H

#include <cstdio>
#include <cstdlib>

static char* ReadEntireFileIntoMemoryAndNullTerminate(char* fileName)
{
    char* result = 0;
    FILE* filePtr;

    filePtr = fopen(fileName,"r");

    if(filePtr)
    {
        //Moves the cursor on the end of the file.
        fseek(filePtr,0,SEEK_END);

        //ftell returns the location where the cursor is on the file.
        size_t fileSize = ftell(filePtr);

        //Move the cursor back to the beginning of the file
        fseek(filePtr,0,SEEK_SET);

        //allocate the needed memory based on file size + 1 (we need one more byte to end with 0).
        result = (char*)(malloc(fileSize + 1));

        //reads the file and stores it into the buffer we just allocated
        fread(result,fileSize,1,filePtr);

        //null terminate our file
        result[fileSize] = '0';

        fclose(filePtr);
    } else
    {
        printf("Could Not Load the file!!!");
        throw;
    }

    return (result);
}

enum TokenType
{
    IDENTIFIER,
    SEMICOLUMN,
    ENDOFSTREAM,
    UNKOWN
};

struct Tokenizer
{
    char* at;
};

struct Token
{
    TokenType tokenType;
    int textLength;
    char* text;
};
inline static bool isAlpha(char c)
{
    bool result = ((c >= 'a') && (c <= 'z')) ||
                  ((c >= 'A') && (c <= 'Z'));

    return result;
}

inline static bool IsWhiteSpace(char c)
{
    bool result = ((c == ' ')||
                  (c == '\t')||
                  (c == '\n')||
                  (c == '\r'));

    return result;
}

static void EatAllWhiteSpace(Tokenizer* tokenizer)
{
    while (IsWhiteSpace(tokenizer->at[0]))
    {
        ++tokenizer->at;
    }
};


static Token GetToken(Tokenizer* tokenizer)
{
    Token token{};

    EatAllWhiteSpace(tokenizer);

    token.textLength = 1;
    token.text = tokenizer->at;

    switch (tokenizer->at[0])
    {
        case '#': {token.tokenType = IDENTIFIER;}
        {
        } break;
        case ';': {token.tokenType = SEMICOLUMN;} break;
        case '\0': {token.tokenType = ENDOFSTREAM;} break;
        default: {token.tokenType = UNKOWN;} break;
    }

    ++tokenizer->at;

    return token;
};

struct AssetToken
{
    char* assetType;
    char* assetPath;
    char* assetName;
};

struct AssetCollection
{
    AssetToken* assetTokens;
    size_t validCount = 0;
};

static char* ParseAssetType(Tokenizer* tokenizer)
{
    char* first = tokenizer->at - 1;

    while (isAlpha(tokenizer->at[0]))
    {
        tokenizer->at++;
    }

    //minus one here because we advanced one past ur alpha token in the end again.
    size_t textLength = (tokenizer->at-1) - first;

    char* assetType = (char*)(malloc(textLength ));
    for (int i = 0; i < textLength; ++i)
    {
        if(first[i+1] != ' ')
            assetType[i] = first[i+1];
    }

    assetType[textLength ] = '\0';
    return assetType;
}

static char* ParseAssetPath(Tokenizer* tokenizer)
{
    char* first = tokenizer->at +1;

    int whiteSpaceCount = 0;

    //here we need to get the path
    while(tokenizer->at[0] != ';')
    {
        if(IsWhiteSpace(tokenizer->at[0])) whiteSpaceCount++;

        tokenizer->at++;
    }

    size_t length = tokenizer->at - first;
    size_t realLength = length - whiteSpaceCount;

    char* path = (char*)(malloc(realLength +1 ));

    int index = 0;
    for (int i = 0; i < length; ++i)
    {
        if(!IsWhiteSpace(first[i])) {
            path[index] = first[i];
            index++;
        }
    }

    path[realLength  ] = '\0';

    return path;
}

static char* ParseAssetName(Tokenizer* tokenizer)
{
    char* first = tokenizer->at ;

    int whiteSpaceCount = 0;

    //here we need to get the path
    while(tokenizer->at[0] != ':')
    {
        if(IsWhiteSpace(tokenizer->at[0])) whiteSpaceCount++;

        tokenizer->at++;
    }

    size_t length = tokenizer->at - first;
    size_t realLength = length - whiteSpaceCount;

    char* path = (char*)(malloc(realLength ));

    int index = 0;
    for (int i = 0; i < length; ++i)
    {
        if(!IsWhiteSpace(first[i])) {
            path[index] = first[i];
            index++;
        }
    }

    path[realLength] = '\0';

    return path;
}

static AssetCollection ParseAssetFile(char* fileName, size_t maxNrOfAssets = 100)
{
   char* fileContent =  ReadEntireFileIntoMemoryAndNullTerminate(fileName);

   bool parsing = true;

   Tokenizer tokenizer {};
   tokenizer.at = fileContent;

   AssetToken* assetTokens = (AssetToken*)(malloc(maxNrOfAssets * sizeof(AssetToken)));
   int validSize = 0;

   while (parsing)
   {
       Token token = GetToken(& tokenizer);

       AssetToken* assetToken = &assetTokens[validSize];

       switch (token.tokenType)
       {
           case IDENTIFIER:
           {
               assetToken->assetType = ParseAssetType(&tokenizer);
               assetToken->assetName = ParseAssetName(&tokenizer);
               assetToken->assetPath = ParseAssetPath(&tokenizer);

           }break;
           case SEMICOLUMN:
           {
               ++validSize;
           }break;
           case ENDOFSTREAM:
           {
                parsing = false;

           }break;
           case UNKOWN:
           {
               //printf("%d: %. *s\n",token.tokenType,token.textLength,token.text);
           }
           break;
       }
   }

   AssetCollection assetCollection{};
   assetCollection.assetTokens = assetTokens;
   assetCollection.validCount = validSize;
   return assetCollection;

};

#endif //CROW_ASSETPARSER_H
