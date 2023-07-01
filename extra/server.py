### uvicorn server:app --reload --port 8000


import market
from typing import Union
import os
import random
import uvicorn
from fastapi import FastAPI

app = FastAPI()
print("was")

m = MarketPlace()

