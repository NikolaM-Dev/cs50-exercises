from typing import Literal, TypedDict

Quote = TypedDict("Quote", {"name": str, "price": float, "symbol": str})
SearchedStock = TypedDict("SearchedStock", {"id": int, "shares": int})
User = TypedDict("User", {"id": int, "name": str, "hash": str, "cash": int})
Stock = TypedDict("Stock", {"name": str, "symbol": str, "shares": int})
Transaction = TypedDict(
    "Transaction",
    {
        "name": str,
        "symbol": str,
        "shares": int,
        "total": float,
        "price": float,
        "transaction_type": Literal["sale", "purchase"],
        "created_at": str,
    },
)
PortfolioItem = TypedDict(
    "PortfolioItem",
    {"name": str, "symbol": str, "shares": int, "price": str, "total": str},
)
