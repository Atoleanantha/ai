
def NQueen(n):
    if(n==0):
        return True 
    
    for i in range(N):
        for j in range(N):
            if(board[i][j]!=1 and isSafe(i,j)):
                board[i][j]=1
                if(NQueen(n-1)==True):
                    return True
                board[i][j]=0
    return False

def isSafe(i,j):
    for m in range(N):
        if(board[i][m]==1 or board[m][j]==1):
            return False
    for m in range(N):
            for n in range(N):
                if i+j ==n+m or i-j ==m-n:
                    if board[m][n]==1:
                        return False
    return True