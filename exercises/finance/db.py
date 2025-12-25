from functools import wraps
from typing import Literal, cast

from cs50 import SQL  # type: ignore

from models import Quote, SearchedStock, Stock, Transaction, User

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


def wrap_transaction(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        db.execute("BEGIN")
        try:
            result = func(*args, **kwargs)
        except Exception:
            db.execute("ROLLBACK")
            raise
        else:
            db.execute("COMMIT")
            return result

    return wrapper


def users_find_by_username(username: str) -> User | None:
    """Finds a user by username"""

    users: list[User] = db.execute(
        """
        SELECT
            *
        FROM
            users
        WHERE
            username = ?;
        """,
        username,
    )

    if len(users) != 1:
        return None

    return users[0]


def users_find_by_id(id: int) -> User | None:
    """Finds a user by id"""

    users: list[User] = db.execute(
        """
        SELECT
            *
        FROM
            users
        WHERE
            id = ?;
        """,
        id,
    )

    if len(users) != 1:
        return None

    return users[0]


def users_find_cash(id: int) -> float | None:
    """Finds the user cash"""

    users: list[User] = db.execute(
        """
        SELECT
            cash
        FROM
            users
        WHERE
            id = ?;
        """,
        id,
    )

    if len(users) != 1:
        return None

    return users[0]["cash"]


@wrap_transaction
def users_create(username: str, hash: str) -> None:
    """Creates a new user"""
    db.execute(
        """
            INSERT INTO
                users (username, hash)
            VALUES
                (?, ?);
        """,
        username,
        hash,
    )


@wrap_transaction
def users_update_password(id: int, hash: str) -> None:
    """Updates user password"""
    db.execute(
        """
            UPDATE
                users
            SET
                hash = ?
            WHERE
                id = ?;
        """,
        hash,
        id,
    )


@wrap_transaction
def quote_search_history_create(user_id: int, quote: Quote) -> None:
    """Create a new record in `quote_search_history` by the user"""

    db.execute(
        """
            INSERT INTO
                quote_search_history (name, symbol, price, created_at, user_id)
            VALUES
                (?, ?, ?, datetime('now'), ?);
        """,
        quote["name"],
        quote["symbol"],
        quote["price"],
        user_id,
    )


def quote_search_history_find_many(user_id: int) -> list[Quote]:
    """Finds the last 10 quote search's by the user"""

    quotes = cast(
        list[Quote],
        db.execute(
            """
            SELECT
                name,
                symbol,
                price,
                DATETIME(created_at, 'localtime') AS created_at
            FROM
                quote_search_history
            WHERE
                user_id = ?
            ORDER BY
                id DESC
            LIMIT
                10;
        """,
            user_id,
        ),
    )

    return quotes


@wrap_transaction
def users_update_cash(
    user_id: int,
    cash: float,
    amount: float,
    operation: Literal["deposit", "withdrawal"],
) -> None:
    """Updates the cash from the user based on the operation"""
    total_cash = cash
    if operation == "deposit":
        total_cash += amount
    else:
        total_cash -= amount

    if total_cash < 0:
        raise ValueError("You don't have enough cash to complete that purchase.")

    db.execute(
        """
        UPDATE
            users
        SET
            cash = ?
        WHERE
            id = ?;

        """,
        total_cash,
        user_id,
    )


def stocks_find_one(user_id: int, symbol: str) -> SearchedStock | None:
    """Finds one stock by user_id and symbol"""
    stocks = cast(
        list[SearchedStock],
        db.execute(
            """
                SELECT
                    id,
                    shares
                FROM
                    stocks
                WHERE
                    user_id = ?
                    AND symbol = UPPER(?);
            """,
            user_id,
            symbol,
        ),
    )

    if len(stocks) != 1:
        return None

    return stocks[0]


@wrap_transaction
def stocks_create(user_id: int, shares: int, quote: Quote) -> None:
    """Creates a stock"""
    db.execute(
        """
            INSERT INTO
                stocks (name, symbol, shares, user_id)
            VALUES
                (?, ?, ?, ?);
        """,
        quote["name"],
        quote["symbol"],
        shares,
        user_id,
    )


@wrap_transaction
def stocks_update(
    stock_id: int, shares: int, amount: int, operation: Literal["deposit", "withdrawal"]
) -> None:
    """Updates the shares based on the operation"""
    total_shares = shares
    if operation == "deposit":
        total_shares += amount
    else:
        total_shares -= amount

    if total_shares < 0:
        raise ValueError("You don't have enough shares.")

    db.execute(
        """
            UPDATE stocks
            SET
                shares = ?
            where
                id = ?;
        """,
        total_shares,
        stock_id,
    )


def stocks_find_many(user_id: int) -> list[Stock]:
    """Finds all the stocks in the user portfolio"""
    return db.execute(
        """
            SELECT
                name,
                symbol,
                shares
            FROM
                stocks
            WHERE
                user_id = ?
                AND shares > 0;
        """,
        user_id,
    )


@wrap_transaction
def transctions_create(
    transaction_type: Literal["sale", "purchase"],
    shares: int,
    price: float,
    user_id: int,
    stock_id: int,
) -> None:
    """Creates a transaction"""
    db.execute(
        """
            INSERT INTO
                transactions (transaction_type, shares, price, created_at, user_id, stock_id)
            VALUES
                (?, ?, ?, datetime('now'), ?, ?);
        """,
        transaction_type,
        shares,
        price,
        user_id,
        stock_id,
    )


def transactions_find_many(user_id: int) -> list[Transaction]:
    """Finds transactions history based on the user"""
    return db.execute(
        """
            SELECT
                DATETIME(transactions.created_at, 'localtime') AS created_at,
                stocks.symbol,
                stocks.name,
                transactions.transaction_type,
                transactions.shares,
                transactions.price,
                SUM(transactions.shares * transactions.price) AS total
            FROM
                transactions
                JOIN stocks ON stocks.id = transactions.stock_id
            WHERE
                transactions.user_id = ?
            GROUP BY
                stocks.symbol,
                transactions.transaction_type
            ORDER BY
                transactions.id DESC;
        """,
        user_id,
    )
