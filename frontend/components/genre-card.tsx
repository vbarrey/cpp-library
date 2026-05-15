import { Genre } from "@/lib/api";

interface GenreCardProps {
    genre: Genre;
}

export default function GenreCard({ genre }: GenreCardProps) {
    return (
        <div className="border border-gray-200 rounded-lg p-4">
            <h2 className="text-lg font-semibold text-center">{genre.name}</h2>
        </div>
    );
}