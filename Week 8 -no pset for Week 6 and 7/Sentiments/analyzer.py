import nltk
import cs50


class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        
        #create 2 sets
        self.positives= set()
        self.negatives= set()
       
        #load positives
        file_p = open(positives, "r")
        for line in file_p:
            if line.startswith(';'):
                pass
            else:
                self.positives.add(line.rstrip(' \n'))
        file_p.close()
       
       #load negatives
        file_n = open(negatives, "r")
        for line in file_n:
            if line.startswith(';'):
                pass
            else:
                self.negatives.add(line.rstrip(' \n'))
        file_n.close()
        
    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        #set score to 0 and create tokens list from input
        score=0
        tokenizer = nltk.tokenize.TweetTokenizer()  
        tokens= tokenizer.tokenize(text)
        #itterate over each line in tokens list and adjust score accordingly     
        for line in tokens:
            if line.lower() in self.positives:
               score+=1
            elif line.lower() in self.negatives:
                score-=1
            else:
                pass
        return score
   
  
