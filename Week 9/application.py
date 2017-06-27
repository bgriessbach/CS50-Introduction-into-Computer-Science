from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp
from passlib.context import CryptContext
from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd
pwd_context = CryptContext(schemes=["pbkdf2_sha256", "des_crypt"], deprecated="auto")

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/bought", methods=["GET", "POST"])
@login_required
def bought():
    if request.method=="POST":
        return redirect(url_for("index"))
    else:
        return redirect(url_for("bought"))

@app.route("/sold", methods=["GET", "POST"])
@login_required
def sold():
    if request.method=="POST":
        return redirect(url_for("index"))
    else:
        return redirect(url_for("sold"))
        
@app.route("/")
@login_required
def index():
    
    #store cash
    row_cash=db.execute("SELECT * FROM users WHERE id= :id", id= session["user_id"])
    Cash=row_cash[0]["cash"]
    
    
    row_stocks_shares=db.execute("SELECT * FROM Ownership WHERE UserID= :id", id= session["user_id"])
    price={}
    total_per_stock={}
    stock_amount={}
    total_sum=None
    
    for rows in range(len(row_stocks_shares)):
        stock= row_stocks_shares[rows]["Stock"]
        Quote=lookup(stock)
        price[stock]=Quote["price"]
        total_per_stock[stock]=Quote["price"]*row_stocks_shares[rows]["Total_Amount"]
        stock_amount[stock]=row_stocks_shares[rows]["Total_Amount"]
    
    total_sum= Cash+sum(total_per_stock.values())
    
    return render_template("index.html", cash=Cash, total_sum=total_sum, price=price, total_per_stock=total_per_stock, stock_amount=stock_amount)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    
    if request.method == "POST":
        # ensure quote is submitted
        if not request.form.get("stock") or not request.form.get("amount"):
            return apology("must provide a stock symbol and amount")
        try:
            val= int(request.form.get("amount"))
        except:
            return apology("Please provide a stock amount >0")
        if int(request.form.get("amount"))<=0:
            return apology("Please provide a stock amount >0")
        Quote= lookup(request.form.get("stock"))
        if Quote==None:
            return apology("could not return valid Quote")
        total=(Quote["price"])*(int(request.form.get("amount")))
        
        #check user has enough cash to afford purchase
        row=db.execute("SELECT cash FROM users WHERE id = :id", id= session["user_id"])
        Cash = row[0]["cash"]
        if total>Cash:
            return apology("Not enough cash")
        
        #update client stock Ownership database
        exists=db.execute("SELECT * FROM Ownership WHERE UserID = :id AND Stock = :stock", id= session["user_id"], stock=request.form.get("stock").upper())
        if len(exists)==0:
            db.execute("INSERT INTO Ownership(UserID, Stock, Total_Amount) VALUES (:userid, :stock, :amount )", userid= session["user_id"], stock=request.form.get("stock").upper(), amount=request.form.get("amount"))
        else:
            db.execute("UPDATE Ownership SET Total_Amount= Total_Amount + :amount WHERE UserID = :id AND Stock = :stock", amount=request.form.get("amount"), id= session["user_id"], stock=request.form.get("stock").upper())
        
        #update cash amount for user and history of purchase database
        db.execute("UPDATE users SET cash= :cash WHERE id = :id", cash=(Cash-total), id= session["user_id"])
        db.execute("INSERT INTO Records(UserID, Stock, Amount, Price) VALUES (:userid, :stock, :amount, :price )", userid= session["user_id"], stock=request.form.get("stock").upper(), amount=request.form.get("amount"), price= Quote["price"])
        return render_template("bought.html", quote=Quote, amount= request.form.get("amount").upper(), total=total)
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    
    row_records=db.execute("SELECT * FROM Records WHERE UserID= :id", id= session["user_id"])
    return render_template("history.html", row_records=row_records)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # ensure quote is submitted
        if not request.form.get("quote"):
            return apology("must provide a stock symbol")
        Quote= lookup(request.form.get("quote"))
        if Quote==None:
            return apology("could not return valid Quote")

        return render_template("quoted.html", quote=Quote)
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")
        elif not request.form.get("password")==request.form.get("password_dupe"):
            return apology("passwords must match")
        
        # ensure username doesn't already exist
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        if len(rows) != 0:
            return apology("Username already exists")
        
        # add new user to database
        db.execute("INSERT INTO users(username, hash) VALUES (:username, :hash)", username=request.form.get("username"), hash=pwd_context.hash(request.form.get("password")))
        return render_template("login.html")

    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    if request.method == "POST":
        # ensure quote is submitted
        if not request.form.get("stock") or not request.form.get("amount"):
            return apology("must provide a stock symbol and amount")
        try:
            val= int(request.form.get("amount"))
        except:
            return apology("Please provide a stock amount >0")
        if int(request.form.get("amount"))<=0:
            return apology("Please provide a stock amount >0")        
        Quote= lookup(request.form.get("stock"))
        if Quote==None:
            return apology("could not return valid Quote")
        
        #check that user owns as much or less of the stock he wants to sell
        row=db.execute("SELECT Total_Amount FROM Ownership WHERE UserID = :id AND Stock= :stock", id= session["user_id"], stock=request.form.get("stock").upper())
        if len(row)==0:
            return apology("You don't own that Stock")
        total_amount= row[0]["Total_Amount"]
        input_amount= int(request.form.get("amount"))
        if total_amount<input_amount:
            return apology("You don't own enough Stock")
        #delete amounts of stock and delete row if all stock sold
        elif total_amount==input_amount:
            db.execute("DELETE FROM Ownership WHERE UserID = :id AND Stock = :stock", id= session["user_id"], stock=request.form.get("stock").upper())
        else:
            db.execute("Update Ownership SET Total_Amount = Total_Amount - :amount WHERE UserID= :id AND Stock = :stock", amount= int(request.form.get("amount")), id= session["user_id"], stock= request.form.get("stock").upper())

        #add cash for sale
        total_earning=(Quote["price"])*(int(request.form.get("amount")))
        db.execute("UPDATE users SET cash= cash+ :cash WHERE id = :id", cash= total_earning, id= session["user_id"])
        
        #update Purchase History
        db.execute("INSERT INTO Records(UserID, Stock, Amount, Price) VALUES (:userid, :stock, :amount, :price )", userid= session["user_id"], stock=request.form.get("stock").upper(), amount= -input_amount, price=Quote["price"])
        return render_template("sold.html", quote=Quote, amount= request.form.get("amount"), total=total_earning)
    else:
        return render_template("sell.html")
