from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class Message(_message.Message):
    __slots__ = ["message"]
    MESSAGE_FIELD_NUMBER: _ClassVar[int]
    message: str
    def __init__(self, message: _Optional[str] = ...) -> None: ...

class Movie(_message.Message):
    __slots__ = ["cast", "countries", "directors", "fullplot", "genre", "id", "lastupdated", "num_mflix_comments", "plot", "rated", "released", "runtime", "title", "type", "year"]
    CAST_FIELD_NUMBER: _ClassVar[int]
    COUNTRIES_FIELD_NUMBER: _ClassVar[int]
    DIRECTORS_FIELD_NUMBER: _ClassVar[int]
    FULLPLOT_FIELD_NUMBER: _ClassVar[int]
    GENRE_FIELD_NUMBER: _ClassVar[int]
    ID_FIELD_NUMBER: _ClassVar[int]
    LASTUPDATED_FIELD_NUMBER: _ClassVar[int]
    NUM_MFLIX_COMMENTS_FIELD_NUMBER: _ClassVar[int]
    PLOT_FIELD_NUMBER: _ClassVar[int]
    RATED_FIELD_NUMBER: _ClassVar[int]
    RELEASED_FIELD_NUMBER: _ClassVar[int]
    RUNTIME_FIELD_NUMBER: _ClassVar[int]
    TITLE_FIELD_NUMBER: _ClassVar[int]
    TYPE_FIELD_NUMBER: _ClassVar[int]
    YEAR_FIELD_NUMBER: _ClassVar[int]
    cast: _containers.RepeatedScalarFieldContainer[str]
    countries: _containers.RepeatedScalarFieldContainer[str]
    directors: _containers.RepeatedScalarFieldContainer[str]
    fullplot: str
    genre: str
    id: str
    lastupdated: str
    num_mflix_comments: int
    plot: str
    rated: str
    released: str
    runtime: int
    title: str
    type: str
    year: int
    def __init__(self, id: _Optional[str] = ..., plot: _Optional[str] = ..., genre: _Optional[str] = ..., runtime: _Optional[int] = ..., cast: _Optional[_Iterable[str]] = ..., num_mflix_comments: _Optional[int] = ..., title: _Optional[str] = ..., fullplot: _Optional[str] = ..., countries: _Optional[_Iterable[str]] = ..., released: _Optional[str] = ..., directors: _Optional[_Iterable[str]] = ..., rated: _Optional[str] = ..., lastupdated: _Optional[str] = ..., year: _Optional[int] = ..., type: _Optional[str] = ...) -> None: ...

class MoviesList(_message.Message):
    __slots__ = ["movies"]
    MOVIES_FIELD_NUMBER: _ClassVar[int]
    movies: _containers.RepeatedCompositeFieldContainer[Movie]
    def __init__(self, movies: _Optional[_Iterable[_Union[Movie, _Mapping]]] = ...) -> None: ...
