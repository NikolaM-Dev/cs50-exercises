from flask import Flask, redirect, render_template, request, session
from werkzeug.security import check_password_hash, generate_password_hash

from flask_session import Session
from helpers import apology, login_required, lookup, usd
import db
from models import PortfolioItem

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)


@app.context_processor
def utility_processor():
    """Purpose: define extra jinja functions"""

    def format_price(amount: float) -> str:
        return usd(amount)

    return dict(format_price=format_price)


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    stocks = db.stocks_find_many(user_id)
    cash = db.users_find_cash(user_id)
    if not cash:
        return apology("Cash not found", code=404)

    total_portfolio = cash
    portfolio: list[PortfolioItem] = []

    for stock in stocks:
        quote = lookup(stock["symbol"])
        if not quote:
            return apology(
                f"Error finding curren price for {stock['symbol']} Stock", code=424
            )

        total = stock["shares"] * quote["price"]
        total_portfolio += total
        portfolioItem: PortfolioItem = {
            "name": stock["name"],
            "price": usd(quote["price"]),
            "shares": stock["shares"],
            "symbol": stock["symbol"],
            "total": usd(total),
        }

        portfolio.append(portfolioItem)

    return render_template(
        "portfolio.html",
        portfolio=portfolio,
        cash=usd(cash),
        total=usd(total_portfolio),
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = (request.form.get("symbol") or "").strip()
        if not symbol:
            return apology("Symbol is required")

        shares = request.form.get("shares")
        if not shares:
            return apology("Shares is required")
        try:
            shares = int(shares)
        except ValueError:
            return apology("Shares must be a positive number")

        if shares <= 0:
            return apology("Shares must be a positive number")

        quote = lookup(symbol)
        if quote is None:
            return apology(f"{symbol.upper()} symbol not found")

        user_id = session["user_id"]

        if not user_id:
            return redirect("/login")

        # Verify budget
        user = db.users_find_by_id(user_id)
        if not user:
            return redirect("/logout")

        total_amount = shares * quote["price"]
        if total_amount > user["cash"]:
            return apology(
                "You don't have enough cash to complete that purchase.", code=409
            )

        stock = db.stocks_find_one(user_id, symbol)
        if not stock:
            db.stocks_create(user_id, 0, quote)
            stock = db.stocks_find_one(user_id, symbol)

        if not stock:
            return apology("Stock not found", code=404)

        db.transctions_create("purchase", shares, quote["price"], user_id, stock["id"])
        db.stocks_update(stock["id"], stock["shares"], shares, "deposit")

        # Update the user cash
        db.users_update_cash(user_id, user["cash"], total_amount, "withdrawal")

        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.transactions_find_many(session["user_id"])
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        username = request.form.get("username")
        if not username:
            return apology("Must provide username", 403)

        # Ensure password was submitted
        password = request.form.get("password")
        if not password:
            return apology("fust provide password", 403)

        # Query database for username
        user = db.users_find_by_username(username)
        # Ensure username exists and password is correct
        if not user or not check_password_hash(user["hash"], password):
            return apology("Invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = user["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = (request.form.get("symbol") or "").strip()
        if not symbol:
            return apology("Symbol is required")

        quote = lookup(symbol)
        if quote is None:
            return apology(f"{symbol.upper()} symbol not found")

        try:
            db.quote_search_history_create(session["user_id"], quote)
        except Exception as exc:
            print(exc)
            return apology("Internal Error Server", 500)

    quotes = db.quote_search_history_find_many(session["user_id"])
    return render_template("quote.html", quotes=quotes)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    username = (request.form.get("username") or "").strip()
    if not username:
        return apology("Username is required")

    password = request.form.get("password")
    if not password:
        return apology("Password is required")

    confirmation = request.form.get("confirmation")
    if not confirmation:
        return apology("Confirmation Password is required")

    if password != confirmation:
        return apology("Passwords doesn't match")

    hash = generate_password_hash(password)
    try:
        db.users_create(username, hash)
    except ValueError:
        return apology("Username already exists", code=409)
    except Exception as exc:
        print(exc)
        return apology("Unhandle problem", code=500)

    return redirect("/login")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "POST":
        symbol = (request.form.get("symbol") or "").strip()
        if not symbol:
            return apology("Symbol is required")

        shares = request.form.get("shares")
        if not shares:
            return apology("Shares is required")
        try:
            shares = int(shares)
        except ValueError:
            return apology("Shares must be a positive number")

        if shares <= 0:
            return apology("Shares must be a positive number")

        stock = db.stocks_find_one(user_id, symbol)
        if not stock:
            return apology("Stock not found")

        if shares > stock["shares"]:
            return apology(
                f"You attempted to sell more {symbol} shares than available", code=409
            )

        quote = lookup(symbol)
        if not quote:
            return apology("Quote not found", code=404)

        user = db.users_find_by_id(user_id)
        if not user:
            return redirect("/logout")

        try:
            db.stocks_update(stock["id"], stock["shares"], shares, "withdrawal")
        except Exception as exc:
            print(exc)
            return apology("Internal Error Server", code=500)

        db.transctions_create("sale", shares, quote["price"], user_id, stock["id"])
        db.users_update_cash(user_id, user["cash"], quote["price"] * shares, "deposit")

        return redirect("/")

    stocks = db.stocks_find_many(user_id)
    return render_template("sell.html", stocks=stocks)


@app.route("/change-password", methods=["POST"])
@login_required
def change_password():
    """Change user password"""
    previous_password = request.form.get("previous")
    if not previous_password:
        return apology("Previous Password is required")

    password = request.form.get("password")
    if not password:
        return apology("Password is required")

    confirmation = request.form.get("confirmation")
    if not confirmation:
        return apology("Confirmation Password is required")

    user_id = session["user_id"]
    user = db.users_find_by_id(user_id)
    if not user:
        return redirect("/logout")

    if not check_password_hash(user["hash"], previous_password):
        return apology("Previous Password doesn't match", code=409)

    if password != confirmation:
        return apology("Passwords doesn't match", code=409)

    if check_password_hash(user["hash"], password):
        return apology(
            "Change to another password different from the current one", code=409
        )

    hash = generate_password_hash(password)
    db.users_update_password(user_id, hash)

    return redirect("/logout")
