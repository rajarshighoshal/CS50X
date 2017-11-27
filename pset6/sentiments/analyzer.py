import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        
        # set for positive words
        self.positivesSet = set()
        # open file containing positives in read mode
        file = open(positives, 'r')
        # reading each lines which aren't starting with ;
        for line in file:
            if line.startswith(';') == False:
                self.positivesSet.add(line.rstrip('\n'))
        # close file
        file.close()
        
        # set for negative words
        self.negativesSet = set()
        # open file containing negatives in read mode
        file = open(negatives, 'r')
        # reading each lines which aren't starting with ;
        for line in file:
            if line.startswith(';') == False:
                self.negativesSet.add(line.rstrip('\n'))
        # close file
        file.close()

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        # instantiate tokenizer
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        
        # calculating sum of positive and negative
        score = 0
        # checking of postive, negative or neutral
        for word in tokens:
            if word.lower() in self.positivesSet:
                score += 1
            elif word.lower() in self.negativesSet:
                score -= 1
            else:
                continue
        
        return score
