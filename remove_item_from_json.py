# this could remove the {"key":value} from the strings.
json_obj = json.loads(strings)
json_obj.pop("key")
