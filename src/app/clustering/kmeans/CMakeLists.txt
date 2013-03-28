project(kmeans)

file(GLOB KMEANS_SOURCE
	"*.hpp"
	"*.cpp"
	)

add_executable(kmeans ${KMEANS_SOURCE})