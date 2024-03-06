FROM python:3.9

ADD testGroundTruthGenerator.py .

RUN pip install numpy

RUN pip install chess

CMD ["python", "./testGroundTruthGenerator.py"]