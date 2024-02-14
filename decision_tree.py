from collections import Counter
from sklearn.tree import DecisionTreeClassifier
from sklearn.preprocessing import LabelEncoder
import pandas as pd
import numpy as np
import random

class CustomDecisionTree:
    def __init__(self, max_depth=10, random_state=42):  # Remove n_estimators
        self.tree = DecisionTreeClassifier(
            max_depth=max_depth,  # Set your desired max depth
            random_state=random_state,
            min_samples_split=2,  # Modify min_samples_split if needed
            min_samples_leaf=1  # Modify min_samples_leaf if needed
        )
        self.label_encoders = {}

    def preProcess(self, dataset):
        processed_dataset = [row.copy() for row in dataset]  # Create a copy of the original dataset
        for x, row in enumerate(dataset):
            for y, value in enumerate(row):
                if isinstance(value, str) and '?' in value:
                    subset = []
                    start = max(0, x - 60)
                    end = min(len(dataset), x + 60)
                    for i in range(start, end):
                        if '?' not in dataset[i][y]:
                            subset.append(dataset[i][y])
                    if subset:
                        majorityValue = Counter(subset).most_common(1)[0][0]
                        processed_dataset[x][y] = majorityValue
        return processed_dataset

    def train(self, dataset):
        processed_dataset = self.preProcess(dataset)
        # Shuffle the dataset
        random.shuffle(processed_dataset)
        processed_df = pd.DataFrame(processed_dataset)
        processed_df.columns = ['attr_' + str(i) for i in range(processed_df.shape[1] - 1)] + ['class']

        for col in processed_df.columns[:-1]:
            if processed_df[col].dtype == 'object':
                le = LabelEncoder()
                processed_df[col] = le.fit_transform(processed_df[col])
                self.label_encoders[col] = le

        train_size = int(len(processed_dataset) * 0.7)
        X_train = processed_df.drop('class', axis=1)[:train_size]
        y_train = processed_df['class'][:train_size]

        self.tree.fit(X_train, y_train)

    def predict(self, dataset):
        processed_dataset = self.preProcess(dataset)
        processed_df = pd.DataFrame(processed_dataset)
        processed_df.columns = ['attr_' + str(i) for i in range(processed_df.shape[1])]

        for col, encoder in self.label_encoders.items():
            if col in processed_df.columns:
                processed_df[col] = encoder.transform(processed_df[col])

        test_size = int(len(processed_df) * 0.3)
        num_features = processed_df.shape[1] - 1
        X_test = processed_df.iloc[-test_size:, :num_features]

        predictions = self.tree.predict(X_test)
        #predictions = self.dt.predict(X_test)
        print(predictions.size)
        return predictions
    
    # open the txt with the dataset
with open("dataset.txt", "r") as file:
    data = file.readlines()

# store data in a 2d array
dataset = []

# filter through the txt file and fill the 2d array with the all the proper data types
for record in data:

    attributes = record.strip().split(",")

    totalAttributes = []

    for attribute in attributes:
        if attribute.strip().isdigit():
            totalAttributes.append(int(attribute.strip()))
        elif attribute.strip().replace('.','',1).isdigit():
            totalAttributes.append(float(attribute.strip()))
        else:
            totalAttributes.append(attribute.strip())
    dataset.append(totalAttributes)

decision_tree = CustomDecisionTree()

decision_tree.train(dataset)

processed_dataset = decision_tree.preProcess(dataset)

#Extract values from the last column for the last 70% of rows
start = int(0.7 * len(dataset))
labels = [row[-1] for row in dataset[start:]]
print('Labels:',labels)

predictions = decision_tree.predict(dataset)
print('Predictions:', predictions)

correct_predictions = sum(1 for true_label, pred_label in zip(labels, predictions) if true_label == pred_label)
total_samples = len(labels)
accuracy = correct_predictions / total_samples * 100

print(f"Accuracy: {accuracy:.2f}%")