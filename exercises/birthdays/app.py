from typing import TypedDict

from cs50 import SQL
from flask import Flask, redirect, render_template, request
from flask.sansio.scaffold import T_after_request

Birthday = TypedDict("Birthday", {"id": int, "name": str, "month": int, "day": int})

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

# Range of the days based on the month
MONTHS_DAYS = {
    1: 31,
    2: 29,
    3: 31,
    4: 30,
    5: 31,
    6: 30,
    7: 31,
    8: 31,
    9: 30,
    10: 31,
    11: 30,
    12: 31,
}


@app.after_request
def after_request(
    response: T_after_request,
) -> T_after_request:
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
def index():
    """Render the homepage showing stored birthdays."""
    birthdays: list[Birthday] = db.execute("SELECT * FROM birthdays")
    return render_template("index.html", birthdays=birthdays)


def validate_birthday() -> tuple[list[str], Birthday]:
    """Return validation errors and parsed birthday data from the form."""
    errors: list[str] = []
    birthday: Birthday = {}

    name = request.form.get("name").strip()
    if not name:
        errors.append("Name is required")
    birthday["name"] = name

    try:
        birthday["month"] = int(request.form.get("month"))
    except ValueError:
        errors.append("Month must be a number in the 1-12 range")

    try:
        birthday["day"] = int(request.form.get("day"))
    except ValueError:
        errors.append("Day must be a number")

    if birthday.get("month") and birthday.get("day"):
        try:
            max_day = MONTHS_DAYS[birthday["month"]]
            if birthday.get("day") > max_day:
                errors.append(
                    f"Day must be in the range 1-{max_day} based on the month"
                )
        except KeyError:
            errors.append("Month must be a number in the 1-12 range")

    return errors, birthday


@app.route("/create", methods=["POST"])
def create():
    """Validate submission and add a birthday record, or re-render with errors."""
    errors, birthday = validate_birthday()
    if not errors:
        db.execute(
            "INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)",
            birthday["name"],
            birthday["month"],
            birthday["day"],
        )
        return redirect("/")

    birthdays: list[Birthday] = db.execute("SELECT * FROM birthdays")
    return render_template("index.html", birthdays=birthdays, errors=errors)


@app.route("/delete/<id>", methods=["POST"])
def delete(id: str):
    """Delete the birthday with the given ID and return to the homepage."""
    db.execute("DELETE FROM birthdays WHERE id = ?", id)
    return redirect("/")


@app.route("/edit/<id>", methods=["GET"])
def edit(id: str):
    """Render the form for editing the birthday that matches the ID."""
    birthdays = db.execute("SELECT * FROM birthdays WHERE id = ?", id)
    return render_template("edit.html", birthday=birthdays[0])


@app.route("/update/<id>", methods=["POST"])
def update(id: str):
    """Validate updates for a birthday, apply them, or show errors with the form."""
    errors, birthday = validate_birthday()
    if not errors:
        db.execute(
            "UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id = ?",
            birthday["name"],
            birthday["month"],
            birthday["day"],
            id,
        )

        return redirect("/")

    # Preserve id route
    birthday["id"] = int(id)
    return render_template("edit.html", birthday=birthday, errors=errors)
