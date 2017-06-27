from flask import Flask, redirect, render_template, request, url_for
import os
import sys
import helpers
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name, count=100)
    if tweets==None:
        sys.exit("Tweets not found")
   
     # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")

    # instantiate analyzer
    analyzer = Analyzer(positives, negatives)
    
    #analyse tweets and count positives, negatives and neutrals
    counter_positives, counter_negatives, counter_neutrals = 0.0, 0.0, 0.0
    for line in tweets:
        score = analyzer.analyze(line)
        if score > 0.0:
            counter_positives+=1
        elif score < 0.0:
            counter_negatives+=1
        else:
            counter_neutrals+=1
    total_tweets= counter_positives+counter_negatives+counter_neutrals
    
    #generates a chart that accurately depicts those sentiments as percentages.
    positive, negative, neutral = 100.0*counter_positives/total_tweets, 100.0*counter_negatives/total_tweets, 100.0*counter_neutrals/total_tweets

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
