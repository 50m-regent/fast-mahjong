# fast-mahjong

## Requirements
- C++
    - GCC 9.2 以降
- Python
    - Python 3.11 以降

## Installation
Windows では、WSL (Windows Subsystem for Linux) 2 を用いる
- https://learn.microsoft.com/ja-jp/windows/wsl/install 参照

- GCC
    - Mac
        - https://qiita.com/DaikiSuyama/items/09f5aa399aad37783146 参照
    - Windows
        - WSL2 を用い、Linux と同様に行う
    - Linux 
        - ```sudo apt install build-essential``` でインストール

- Pyenv
    - Mac
        - https://zenn.dev/kenghaya/articles/9f07914156fab5 参照
    - Windows
        - WSL2 を用い、Linux と同様に行う
    - Linux
        - https://zenn.dev/hr0t15/articles/8ae3564bde2cce 参照
- Poetry
    - Mac 
        - https://zenn.dev/rihito/articles/1b096b1f695f06 参照
    - Windows
        - WSL2 を用い、Linux と同様に行う
    - Linux
        - 以下を行う
        ```bash
        curl -sSL https://install.python-poetry.org | python3 -
        poetry --version
        ```
        ```Poetry (version 1.5.1)``` などと表示されればインストールが完了しています

## How to Use
1. GitHub からリポジトリをクローンします。
    ```bash
    git clone https://github.com/50m-regent/fast-mahjong.git
    cd fast-majong
    ```
2. Pyenv で Python 3.11 をインストールし、```fast-mahjong``` ディレクトリ内の Python 環境を Python 3.11 に設定します。
    ```bash
    pyenv install 3.11
    pyenv local 3.11
    ```
3. poetry の仮想環境に入ります。
    ```bash
    poetry shell
    ```
4. 必要なライブラリをインストールします。
    ```
    poetry install
    ```